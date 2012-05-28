/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  driver.c
  Provides the driver function for the TDF->DEC Alpha translator.
*/

#include <stdlib.h>

#include "config.h"

#include "basicread.h"
#include "flags.h"
#include "main_reads.h"
#include "flpt.h"
#include "externs.h"
#include "installglob.h"
#include "machine.h"
#include "exp.h"
#include "dump_distr.h"
#include "file.h"
#include "fail.h"
#include "version.h"
#include "reader_v.h"
#include "construct_v.h"
#include "symbol.h"
#include "bool.h"

FILE *as_file;		/* assembly file */
FILE *ba_file;

#define SUCCESS 0
#define FAILURE 1
#ifndef compile_date
#ifdef __DATE__
#define compile_date __DATE__
#else
#error "compile_date is not set"
#define compile_date	"04/07/71"
#endif
#endif
int use_umulh_for_div;
bool do_scheduling = TRUE;
bool fail_with_denormal_constant = TRUE;
bool treat_denorm_specially = FALSE;
bool trap_all_fops = FALSE;
bool do_extern_adds = FALSE;

static int infoopt = FALSE;	/* set if the -V option has been invoked */
static bool produce_symbolic_assembler = FALSE;

void
printinfo(void)
{
  (void)fprintf(stderr,"DRA TDF DEC Alpha/OSF1 translator %d.%d.%d:(TDF version %d.%d)\n",
		target_version,target_revision,target_patchlevel,
		MAJOR_VERSION,MINOR_VERSION);
  (void)fprintf(stderr,"reader %d.%d: ",reader_version,reader_revision);
  (void)fprintf(stderr,"construct %d.%d: \n",construct_version,
		construct_revision);
  (void)fprintf(stderr,"installer compilation %s\n",compile_date);
  return;
}

void
out_rename(char *oldid, char *newid)
{
  UNUSED(oldid);
  UNUSED(newid);
  return;
}

int
get_switch(char option, int range_max)
{
  int val = option - '0';
  if (val>=0 && val <= range_max){
    return val;
  }	
  else {
    (void)fprintf(stderr,"alphatrans: error : illegal option value : 0 .. %d expected\n",range_max);
    exit(EXIT_FAILURE);
  }
  return 0;
}



/*
  Reads and processes a command line option.
*/
void
process_flag(char *option)
{
  switch(option[1]){
   case 'A':
    /* alloca switching */
    do_alloca = get_switch(option[2],1);
    break;
   case 'B':
    /* big floating point constants -> infinity */
    break;
   case 'C':
    do_loopconsts = get_switch(option[2],1);
    break;
   case 'D':
    failer("no PIC code available");
    exit(EXIT_FAILURE);
   case 'E':
    extra_checks = 0;
    break;
   case 'F':
    do_foralls = get_switch(option[2],1);
    break;
   case 'H':
    diagnose = 1;
    do_inlining = 0;
    do_loopconsts = 0;
    do_foralls = 0;
    do_dump_opt = 0;
    do_alloca = 0;
    break;
   case 'I':
    do_inlining=get_switch(option[2],1);
    break;
   case 'K':
    fprintf(stderr,"alphatrans: [-K..] -> only one kind of processor is supported\n");
    break;
   case 'M':
    strict_fl_div = get_switch(option[2],1);
    break;
   case 'P':
    do_profile = 1;
    break;
   case 'Q':
    exit(EXIT_SUCCESS);
    break;
   case 'R':
    round_after_flop = get_switch(option[2],1);
    break;
   case 'S':
    produce_symbolic_assembler = TRUE;
    break;
   case 'U':
    do_unroll = get_switch(option[2],1);
    break;
   case 'X':
    do_inlining=0;
    do_loopconsts=0;
#ifdef USE_OLD_UNROLLER
    dostrengths=0;
#endif
    do_special_fns=0;
    do_foralls=0;
    do_dump_opt=0;
    break;
   case 'V':
   case 'v':
   case 'i':
    printinfo();
    infoopt = TRUE;
    break;
   case 'W':
    writable_strings = get_switch(option[2],1);
    break;
   case 'Z':
    report_versions = 1;
    break;
   case 'u':
    use_umulh_for_div = get_switch(option[2],1);
    break;
   case 's':
    do_scheduling = get_switch(option[2],1);
    break;
   case 'd':	
    /* handle IEEE denormals */
     treat_denorm_specially = TRUE;
     switch(get_switch(option[2],2)){
     case 0: /* replace denormal const with 0.0 (don't do this) */
       alphawarn("Unsupported denormal switch");
       fail_with_denormal_constant = FALSE;
       break;
     case 1: /* error if denormal const is encountered */
       fail_with_denormal_constant = TRUE;
       break;
     case 2: 
     /* handle denormals properly (and slowly), by 
       stopping the interleaving of floating point 
       operations and using the OS exception handler */
       treat_denorm_specially = FALSE;
       trap_all_fops = TRUE;
       break;
     }
     break;
  default:
    alphafail(ILLEGAL_FLAG,option);
    break;
  }
}

bool BIGEND = (little_end == 0);
bool do_tlrecursion = 1;
int currentfile = -1;
int mainfile=0;
int majorno = 3;
int minorno = 11;

#define MIN_COMMAND_LINE_ARGS 4

int
main(int argc, char *argv[])
{
  int i;
  int num_flags=0;
  char *aname;	/* name of file for assembly output */
  char *dname;	/* name of file to hold symbol table */
  char *baname;
  char *tname;
  do_inlining=0;
  redo_structfns=1;
  do_foralls=0;
  do_alloca=1;
#if DO_NEW_DIVISION 
  use_umulh_for_div = 1;
#else
  use_umulh_for_div = 0;
#endif
  /* read command line options */
  for(i=1;i<argc;++i){
    if(argv[i][0] == '-'){
      num_flags++;
      process_flag(argv[i]);
    }
  }
  if((argc-num_flags)<MIN_COMMAND_LINE_ARGS){
    if(infoopt){
      exit(EXIT_SUCCESS);
    }
    else{
      alphafail(TOO_FEW_PARAMETERS);
    }
  }

  /* the files are passed in the order .t .G .T .s */

  if(produce_symbolic_assembler){
      aname = argv[argc-1];
      as_file = open_file(aname,WRITE);
      argc--;
  }
  baname = argv[argc-2];
  dname = argv[argc-1];
  tname = argv[argc-3];

  ba_file = open_file(baname,WRITE);
  if(!initreader (tname)) alphafail(OPENING_T_FILE,tname);
  init_flpt();
#include "inits.h"
  top_def = (dec*)0;
  local_prefix="$$";
  name_prefix="";
#if DO_SCHEDULE
  if(do_scheduling){
    initialise_scheduler();
  }
#endif

  (void)d_capsule();
  output_symtab(dname);
#if DO_SCHEDULE
  if(do_scheduling){
/*    schduler_finished();*/
  }
#endif
  close_file(as_file);
  close_file(ba_file);
  return SUCCESS;
}







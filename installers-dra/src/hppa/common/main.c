/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#define HPPATRANS_CODE

#include "config.h"

#include "flags.h"		/* for option flags */
#include "tempdecs.h"		/* for tempdecopt */
#include "comment.h"		/* for do_comment */
#include "translat.h"		/* for optim_level, translate () */
#include "main_reads.h"		/* for d_capsule */
#include "basicread.h"	/* for good_trans */
#include "addrtypes.h"		/* for where */
#include "makecode.h"		/* for nowhere */
#include "flpt.h"
#include "exptypes.h"
#include "exp.h"		/* for current_alloc_size */
#include "installglob.h"	/* for top_def */
#include "out.h"
#include "installtypes.h"
#include "version.h"
#include "reader_v.h"
#include "construct_v.h"
#include "externs.h"
#include "hppadiags.h"
#include "frames.h"

#ifdef __DATE__
#define compile_date __DATE__
#else
#define compile_date "unknown date"
#endif

extern int good_trans;
int OPTIM=1;
int gdb,xdb,gcc_assembler;

#define GET_0_1 (arg[2] == '0' ? 0 : 1)

char *local_prefix, *name_prefix;

bool do_tlrecursion = 0;	/* eventually to be moved to flagsdescs.h */



/* only advertise options in manual page, other debugging options available as well */
static char usage_mess[] = "usage ( s = 0|1 ): trans [-As] [-Bs] [-Cs] [-D] [-d] [-Es] [-Fs] [-Gs] [-H] [-h] [-Is] [-K] [-Ms] [-O] [-P] [-Q] [-Rs] [-T] [-Us] [-V] [-v] [-W] [-X] [-Z] TDF-capsule output-as-file\n";

static int init_trans(char *, char *) ; /* forward reference */

int main
(int argc, char ** argv)
{
  int a=1;
  char *arg;
  bool errflg = 0;
  bool versionflg = 0;
  char *infname= (char*)0;
  char *outfname= (char*)0;


  /* initialise output file */
  outf = stdout;

  /* errors messages are output on stdout, ensure they get out */
  setbuf(stdout, NULL);

   /* set defaults for options */

   do_unroll = 1;                   /* do unroll loops */
   do_inlining = 1;                /* do inline */
   do_special_fns = 1;            /* do special functions */
   do_loopconsts = 1;	         /* remove constants from loops */
   do_foralls = 1;	        /* do foralls optimisation */
   gcc_assembler = 0;
   xdb = 0;
   gdb = 0;
   OPTIM = 1;

  redo_structfns = 0;	  /* procs delivering structs recast to extra param */
  redo_structparams = 1; /* struct and union value parameters indirected   */
  diagnose = 0;		/* -H option for diagnostics */
  do_profile = 0;      /* -P option for profiling info */
  do_alloca = 1;      /* inline alloca       */
  PIC_code = 0;

  /* from tempdecs.c */
  tempdecopt = 1;		/* unset by -T option */

  /* from comment.c */
  do_comment = 0;		/* implement -C option */

  /* from translat.c */
  optim_level = 2;		/* default equiv to -O2 */


   /* process program args */
   while (a < argc && (arg = argv[a], arg[0] == '-'))
     {
       switch (arg[1])
	 {
	 case 'A': do_alloca = GET_0_1; break;
	 case 'B': flpt_const_overflow_fail = GET_0_1; break;
	 case 'C': do_loopconsts = GET_0_1; break;
	 case 'D':
           {
             /* -D emulates cc's +Z flag */
             PIC_code = GET_0_1;
             plusZ = 1;
             break;
	   }
	 case 'd':
           {
             /* -d emulates cc's +z flag */
             PIC_code = GET_0_1;
             plusZ = 0;
             break;
	   }
	 case 'E': extra_checks = 0; break;
	 case 'F': do_foralls = GET_0_1; break;
	 case 'G': gcc_assembler = GET_0_1; break;
	 case 'H':
	   {
#ifdef _SYMTAB_INCLUDED
	        diagnose = 1;
                xdb = 1;
#else
	        fprintf(stderr,"trans warning: XDB diagnostics not supported on this version of hppatrans, -H option ignored\n");
                xdb = 0;
                diagnose = 0;
#endif
	     break;
	   }
         case 'h':
	   {
              diagnose = 1;
              gdb = 1;
              gcc_assembler = 1;
	   }
	 case 'I': do_inlining = GET_0_1; break;
	 case 'K': break;
	 case 'M': strict_fl_div = GET_0_1; break;
	 case 'O' : /* optim_level not applicable to hp_pa */ break;
	 case 'P':
           {
	     do_profile = 1;
	     break;
           }
	 case 'Q': exit(EXIT_SUCCESS); break;
	 case 'R': round_after_flop = GET_0_1; break;
	 case 'T' : /* tempdecopt = 0, not applicable to hp_pa */ break;
	 case 'U': do_unroll = GET_0_1; break;
	 case 'V':
	   {
	     /* print version number */
	     fprintf(stderr,"DERA TDF->HP PA-RISC translator %d.%d: (TDF %d.%d)\nreader %d.%d:\nconstruct %d.%d:\ntranslator compilation date = %s\n ",
		    MAJOR,MINOR,MAJOR_VERSION,MINOR_VERSION,
		    reader_version,reader_revision,construct_version,
		    construct_revision,compile_date);
	     versionflg = 1;
	     break;
	   }
	 case 'W': break;
	 case 'X':
	   {
	     /* disable all optimisations */
	     tempdecopt = 0;
	     do_inlining = 0;
	     do_loopconsts = 0;
	     do_foralls = 0;
	     do_tlrecursion = 0;
	     do_unroll = 0;
	     break;
	   }
	 case 'Z': report_versions = 1; break;
	 case '?': default:
           {
    	     fprintf(stderr, "%s : unknown option, \"%s\"\n", "trans", arg);
             errflg = 1; break;
           }
	 }  /* switch */
       a++;
     }

   /* we expect two further filename arguments */
   if (argc == a+2)
     {
       infname = argv[a];
       outfname = argv[a+1];
     }
   else if (argc == a+1)
     {
       infname = argv[a];
       outfname = "-";
     }
   else { errflg = 1; };

   if (errflg)
     {
       if (!versionflg)		/* no complaints for -v */
	 fprintf(stderr, "%s", usage_mess);
       exit(EXIT_FAILURE);
     }

   if (do_profile && PIC_code)
   {
      fprintf(stderr,"hppatrans warning: \"-P\" and \"-D\" are mutually exclusive. \"-P\" ignored.\n");
      do_profile = 0;
   }

   /* Switch off certain optimisations when in diagnostics mode. */
   if (diagnose)
   {
      optim_level = 0;
      tempdecopt = 0;
      do_inlining = 0;
      do_loopconsts = 0;
      do_foralls = 0;
      do_tlrecursion = 0;
      do_unroll = 0;
      OPTIM = 0;
      if (gdb)
         gcc_assembler = 1;
   }

   /* init nowhere */
  setregalt(nowhere.answhere, 0);
  nowhere.ashwhere.ashsize = 0;
  nowhere.ashwhere.ashsize = 0;

  local_prefix = "$";		/* Label prefix */
  crt_labno = 101;		/* First label; avoid conflict with reg nos */
				/* (and backward compatibility) */

   name_prefix = "";

  init_flpt();			/* initialise the floating point array */
#include "inits.h"		/* initialise common parts of translator */
  top_def = (dec *)0;

  if (diagnose)
  {
     init_stab();
  }

  if (init_trans(infname,outfname) || d_capsule() || good_trans)
     exit(EXIT_FAILURE);

  exit_translator();

  /* check for output errors and close the .s file */
  if (ferror(outf)!= 0 || fclose(outf)!= 0)
  {
    fprintf(stderr, "hppatrans: error writing to output file %s\n", outfname);
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

/*
 * Open input and output files.
 */
static int init_trans
(char * infname, char * outfname)
{

  /*
   * Open files.
   */

  if (!initreader(infname))
  {
    fprintf(stderr, "hppatrans: cannot open input file %s\n", infname);
    return 3;
  }

  if (strcmp(outfname, "-") == 0)
  {
    /* "-" by convention means stdout */
    outf = stdout;
  }
  else
  {
    outf = fopen(outfname, "w+");
    if (outf == (FILE *)0)
    {
      fprintf(stderr, "hppatrans: cannot open output file %s\n", outfname);
      return 3;
    }
  }

  return 0;			/* OK */
}

void out_rename
(char * oldid, char * newid)
{
    comment2("renamed %s as %s", oldid, newid);
    return;
}
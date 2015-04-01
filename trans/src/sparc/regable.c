/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <local/ash.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>

#include <main/flags.h>

#include "regable.h"

/*
  DOES A VALUE OF SHAPE s FIT INTO A FIXED REGISTER?
*/

bool 
valregable ( shape s ){
  if ( is_floating ( s->tag ) ) {
    /* Floating point values don't go in fixed registers */
    return 0;
  } 
  else {
    ash a ;
    a = ashof ( s ) ;
    if ( a.ashsize > 32 ) {
      /* Reject anything too big */
      return 0;
    } 
    else if ( s->tag == cpdhd || s->tag == nofhd) {
      /* Compound shapes are not put in registers */
      return 0;
    } 
    else if ( /*a.ashsize == a.ashalign && a.ashalign !=*/ 1 ) {
      /* Bitfields are put in registers */
      return 1;
    }
  }
  return 0;
}


/*
  DOES THE EXPRESSION e FIT INTO A FIXED REGISTER?
*/

bool 
fixregable ( exp e ){
  if ( !isvis ( e ) && !isoutpar ( e) && !isglob ( e ) && !isenvoff(e) &&
       son(e)->tag != caller_name_tag) {
    shape s = sh ( son ( e ) ) ;
    return valregable ( s ) ;
  }
  return 0;
}


/*
  DOES THE EXPRESSION e FIT INTO A FLOATING POINT REGISTER?
*/

bool 
floatregable ( exp e ){
  if ( !isvis ( e ) && !isoutpar ( e) && !isglob ( e ) && !isenvoff(e) &&
       son(e)->tag != caller_name_tag) {
    shape s = sh ( son ( e ) ) ;
    if ( is_floating ( s->tag ) ) {
      if ( (has & HAS_LONG_DOUBLE) && shape_size ( s ) > 64 ) return 0;
      return 1;
    } 
    else {
      return 0;
    }
  }
  return 0;
}


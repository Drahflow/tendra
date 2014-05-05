# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IFNDEF __JUST_POSIX

+SUBSET "va_args" := {
    +SUBSET "va_list" := {
	# This is a hack to hide va_list
	+IFNDEF ~building_libs
	+TYPE ~va_list.1 | va_list.1 ;
	+ELSE
	+TYPE va_list.2 | va_list.2 ;
	+TYPEDEF va_list ~va_list.2 ;
	+ENDIF
    } ;

    %% #pragma TenDRA ident ... allow %%

    +IFNDEF ~building_libs
    +TYPEDEF ~va_list va_list ;
    +ENDIF

    +TYPE __va_t | "~__va_t"  ;
    +MACRO va_list __va_start ( __va_t ) ;

    +TOKEN va_arg # This is tricky
    %% PROC ( EXP lvalue : va_list : e , TYPE t ) EXP rvalue : t : %% ;

    +MACRO void va_end ( lvalue va_list ) ;

%%%
#include <stdarg.h>
#ifndef __COMPLEX_VA_LIST
typedef va_list __va_t ;
#define __va_start( X ) ( ( va_list ) ( X ) )
#endif
%%%

} ;

+DEFINE va_start ( l, i )  %% ( ( void ) ( l = __va_start ( ... ) ) ) %% ;

+ENDIF

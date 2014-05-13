# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c89", "stdio.h.ts" ;

+SUBSET "ctuid" := {
    +FUNC char *ctermid ( char * ) ;
    +FUNC char *cuserid ( char * ) ;
} ;

+CONST int L_ctermid, L_cuserid ;

+FUNC FILE *fdopen ( int, const char * ) ;
+FUNC int fileno ( FILE * ) ;
+FUNC int pclose ( FILE * ) ;
+FUNC FILE *popen ( const char *, const char * ) ;
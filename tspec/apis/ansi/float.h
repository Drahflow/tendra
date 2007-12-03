#
# Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#
# $Id$

+SUBSET "xpg3_ranges" := {
    # These are shared by ansi:float.h and xpg3:limits.h
    +SUBSET "xpg4_ranges" := {
        # These are shared by ansi:float.h and xpg4:limits.h
        +EXP int DBL_DIG ;
        +EXP double DBL_MAX ;
        +EXP int FLT_DIG ;
        +EXP float FLT_MAX ;
    } ;
    +EXP double DBL_MIN ;
    +EXP float FLT_MIN ;
} ;

+EXP double DBL_EPSILON ;
+EXP int DBL_MANT_DIG, DBL_MAX_10_EXP, DBL_MAX_EXP ;
+EXP int DBL_MIN_10_EXP, DBL_MIN_EXP ;

+EXP float FLT_EPSILON ;
+EXP int FLT_MANT_DIG, FLT_MAX_10_EXP, FLT_MAX_EXP ;
+EXP int FLT_MIN_10_EXP, FLT_MIN_EXP ;
+CONST int FLT_RADIX ;
+EXP int FLT_ROUNDS ;

+EXP int LDBL_DIG ;
+EXP long double LDBL_EPSILON ;
+EXP int LDBL_MANT_DIG ;
+EXP long double LDBL_MAX ;
+EXP int LDBL_MAX_10_EXP, LDBL_MAX_EXP ;
+EXP long double LDBL_MIN ;
+EXP int LDBL_MIN_10_EXP, LDBL_MIN_EXP ;

# vim:set filetype=tspec:
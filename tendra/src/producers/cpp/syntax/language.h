/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


#ifndef LANGUAGE_INCLUDED
#define LANGUAGE_INCLUDED


/*
    SOURCE LANGUAGE FLAGS

    These flags control whether the producer is configured for C or C++.
    This configuration indicates C++.
*/

#ifdef LANGUAGE_CPP
#undef LANGUAGE_CPP
#endif

#ifdef LANGUAGE_C
#undef LANGUAGE_C
#endif

#define LANGUAGE_CPP		1
#define LANGUAGE_C		0

#define LANGUAGE_NAME		"C++"
#define LANGUAGE_VERSION	CPP_VERSION


#endif
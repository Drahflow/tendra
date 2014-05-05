# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c89", "stddef.h.ts", "null" (!?) ;
+IMPLEMENT "c/c89", "stddef.h.ts", "size_t" (!?) ;

+FUNC char *strcat ( char *, const char * ) ;
+FUNC int strcmp ( const char *, const char * ) ;
+FUNC char *strcpy ( char *, const char * ) ;
+FUNC size_t strcspn ( const char *, const char * ) ;
+FUNC size_t strlen ( const char * ) ;
+FUNC char *strncat ( char *, const char *, size_t ) ;
+FUNC int strncmp ( const char *, const char *, size_t ) ;
+FUNC char *strncpy ( char *, const char *, size_t ) ;
+FUNC size_t strspn ( const char *, const char * ) ;
+FUNC char *strtok ( char *, const char * ) ;

+IFNDEF ~protect ( "cpp", "cstring" )
# These are overloaded in C++
+FUNC char *strchr ( const char *, int ) ;
+FUNC char *strrchr ( const char *, int ) ;
+FUNC char *strpbrk ( const char *, const char * ) ;
+FUNC char *strstr ( const char *, const char * ) ;
+IFNDEF __JUST_POSIX
+FUNC void *memchr ( const void *, int, size_t ) ;
+ENDIF
+ENDIF

+IFNDEF __JUST_POSIX
+FUNC int memcmp ( const void *, const void *, size_t ) ;
+FUNC void *memcpy ( void *, const void *, size_t ) ;
+FUNC void *memset ( void *, int, size_t ) ;
+FUNC int strcoll ( const char *, const char * ) ;
+FUNC char *strerror ( int ) ;
+FUNC size_t strxfrm ( char *, const char *, size_t ) ;
+IFNDEF __JUST_XPG3
+FUNC void *memmove ( void *, const void *, size_t ) ;
+ENDIF
+ENDIF

/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCALTYPES_INCLUDED
#define LOCALTYPES_INCLUDED

#include <reader/exptypes.h>

#include <construct/installtypes.h>

typedef struct {
    long ashsize;
    long ashalign;
} ash;

extern ash ashof(shape);


#endif /* LOCALTYPES_INCLUDED */

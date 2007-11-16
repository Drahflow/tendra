/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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

/*
 * bostream.c - Binary output stream handling.
 *
 * This file implements the binary output stream facility specified in the
 * file "bostream.h".  See that file for more details.
 */

#include <stdio.h>
#include <stddef.h>

#include "bostream.h"
#include "cstring.h"

ExceptionT * XX_bostream_write_error = EXCEPTION("error writing to binary stream");

void
bostream_init(BOStreamT * bostream)
{
    bostream->name = NULL;
}

BoolT
bostream_open(BOStreamT * bostream,		       char *  name)
{
#ifdef FS_BINARY_STDIO
    if ((bostream->file = fopen(name, "wb")) == NULL) {
	return(FALSE);
    }
#else
    if ((bostream->file = fopen(name, "w")) == NULL) {
	return(FALSE);
    }
#endif /* defined (FS_BINARY_STDIO) */
    bostream->name  = name;
    return(TRUE);
}

void
bostream_assign(BOStreamT * to,			 BOStreamT * from)
{
    to->file  = from->file;
    to->name  = from->name;
}

BoolT
bostream_is_open(BOStreamT * bostream)
{
    return(bostream->name != NULL);
}

void
bostream_write_chars(BOStreamT * bostream,			      unsigned  length ,
			      char *  chars)
{
    unsigned bytes_read = (unsigned)fwrite(chars, sizeof(char),
					    (size_t)length, bostream->file);

    if ((bytes_read != length) && (ferror(bostream->file))) {
	char * name = cstring_duplicate(bostream->name);

	THROW_VALUE(XX_bostream_write_error, name);
	UNREACHED;
    }
}

void
bostream_write_bytes(BOStreamT * bostream,			      unsigned  length ,
			      ByteT *     bytes)
{
    unsigned bytes_read = (unsigned)fwrite(bytes, sizeof(ByteT),
					    (size_t)length, bostream->file);

    if ((bytes_read != length) && (ferror(bostream->file))) {
	char * name = cstring_duplicate(bostream->name);

	THROW_VALUE(XX_bostream_write_error, name);
	UNREACHED;
    }
}

void
bostream_write_byte(BOStreamT * bostream,			     ByteT     byte)
{
    if ((fputc((int)byte, bostream->file) == EOF) &&
	(ferror(bostream->file))) {
	char * name = cstring_duplicate(bostream->name);

	THROW_VALUE(XX_bostream_write_error, name);
	UNREACHED;
    }
}

char *
bostream_name(BOStreamT * bostream)
{
    return(bostream->name);
}

void
bostream_close(BOStreamT * bostream)
{
    if (fclose(bostream->file)) {
	char * name = cstring_duplicate(bostream->name);

	THROW_VALUE(XX_bostream_write_error, name);
	UNREACHED;
    }
    bostream_init(bostream);
}

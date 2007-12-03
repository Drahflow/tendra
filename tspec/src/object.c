/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
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


#include "config.h"
#include "object.h"
#include "hash.h"
#include "name.h"
#include "type.h"
#include "utility.h"
#include "variable.h"


/*
    CREATE A NEW OBJECT

    This routine creates a new object, with name nm and type t.
*/

object *
make_object(char *nm, int t)
{
    object *p;
    alloc_variable(p, object, 1000);
    p->name = nm;
    p->objtype = t;
    p->next = null;
    p->filename = filename;
    p->line_no = line_no;
    return(p);
}


/*
    JOIN TWO LISTS OF OBJECTS

    This routine joins two lists of objects, returning the result.
*/

object *
join_object(object *p, object *q)
{
    object *r = p;
    if (p == null) return(q);
    if (q == null) return(p);
    while (r->next)r = r->next;
    r->next = q;
    return(p);
}


/*
    FIND A SUBSET

    This routine looks up the subset named nm.  The operation for splitting
    nm into its components (which should only be called with preprocessed
    input) needs to be kept in step with subset_name.
*/

object *
make_subset(char *nm)
{
    object *p = search_hash(subsets, nm, no_version);
    if (p == null) {
	char *api = string_copy(nm);
	char *file = null;
	char *subset = null;
	char *s = strchr(api, ':');
	if (s) {
	    *s = 0;
	    file = s + 1;
	    s = strchr(file, ':');
	    if (s) {
		*s = 0;
		subset = s + 1;
	    }
	    if (*file == 0)file = null;
	}
	p = make_object(nm, OBJ_SUBSET);
	p->u.u_info = make_info(api, file, subset);
	p->u.u_info->age = (time_t)0;
	IGNORE add_hash(subsets, p, no_version);
    }
    return(p);
}


/*
    CREATE SUBSET INFORMATION

    This routine creates the subset information for the subset
    api:file:subset.
*/

info *
make_info(char *api, char *file, char *subset)
{
    info *p;
    alloc_variable(p, info, 100);
    p->api = api;
    p->file = file;
    p->subset = subset;
    p->age = date_stamp(filename);
    p->incl = include_name(output_incl_dir, api, file, subset);
    p->src = src_name(output_src_dir, api, file, subset);
    p->block = block_name(api, file, subset);
    p->linkage = "C";
    p->nspace = null;
    p->method = null;
    p->prefix = token_prefix(api, file, subset);
    p->protect = macro_name(PROTECT_PREFIX, api, file, subset);
    p->version = null;
    p->tokens = 0;
    p->implemented = 0;
    p->elements = null;
    return(p);
}


/*
    UPDATE A SUBSET DATESTAMP

    This routine updates the datestamp on the subset p from that on the
    subset q.
*/

void
update_time(object *p, object *q)
{
    if (p && q) {
	time_t tp = p->u.u_info->age;
	time_t tq = q->u.u_info->age;
	if (tp && tq > tp)p->u.u_info->age = tq;
    }
    return;
}


/*
    CREATE A TOKEN

    This routine creates a token called nm (version vers) describing the
    object p.  If this is a real token then the tokens field of the
    current subset is set.
*/

object *
make_token(char *nm, int vers, object *p, int objtype)
{
    object *r = make_object(nm, OBJ_TOKEN);
    r->u.u_obj = p;
    IGNORE add_hash(tokens, r, vers);
    if (crt_object) {
	switch (objtype) {
	    case OBJ_EXTERN:
	    case OBJ_WEAK: {
		break;
	    }
	    default : {
		crt_object->u.u_info->tokens = 1;
		break;
	    }
	}
    }
    return(r);
}


/*
    CREATE AN EXPRESSION

    This routine creates and expression object of type t called nm (version
    vers).
*/

object *
make_exp(char *nm, int vers, int t)
{
    object *r = make_object(nm, t);
    IGNORE add_hash(exps, r, vers);
    r->u.u_type = null ;
    return(r);
}
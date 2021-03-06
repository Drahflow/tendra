/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>

#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include "calculus.h"
#include "check.h"
#include "common.h"
#include "output.h"
#include "type_ops.h"

/*
 *  LIST OF ALL NAMES
 *
 *  This variable contains a list of all the names defined within the algebra.
 */
static NAME *all_names = NULL;

/*
 *  ARRAY OF NAME ERRORS
 *
 *  This array gives all the errors associated with the various name types.
 */
static char *name_error[] = {
	"Type name %s",
	"Auxilliary type name %s",
	"Enumeration constant %s.%s",
	"Structure component %s.%s",
	"Union component %s.%s",
	"Union field component %s.%s.%s",
	"Union map %s.%s",
	"Union map argument %s.%s"
};

/*
 * LOOK UP A NAME
 *
 * This routine looks up the name with type n and components a, b and c in
 * the list of all names.
 */
static NAME *
find_name(int n, char *a, char *b, char *c)
{
	NAME *p;

	for (p = all_names; p != NULL; p = p->next) {
		if (p->type == n && streq(p->text[0], a) &&
		    streq(p->text[1], b) && streq(p->text[2], c)) {
			return p;;
		}
	}

	return NULL;
}

/*
 * CREATE A NAME
 *
 * This routine adds the name with type n and components a, b and c to the
 * list of all names.
 */
static void
make_name(int n, char *a, char *b, char *c)
{
	static int names_left = 0;
	static NAME *names_free = NULL;
	NAME *p;

	p = find_name(n, a, b, c);
	if (p) {
		char buffer[1000];
		sprintf(buffer, name_error[n], a, b, c);
		error(ERR_SERIOUS, "%s already defined (at %s, line %d)",
		      buffer, p->file, p->line);
		return;
	}

	if (names_left == 0) {
		names_left = 1000;
		names_free = xmalloc_nof(NAME, names_left);
	}

	p = names_free + (--names_left);
	p->type = n;
	p->text[0] = a;
	p->text[1] = b;
	p->text[2] = c;
	p->file = crt_file_name;
	p->line = crt_line_no;
	p->next = all_names;

	all_names = p;
}

/*
 * EXTRACT NAMES FROM AN IDENTIFIER
 *
 * This routine assigns the names from the identifier id into na and nb.
 * It also sets the current file position to the location of id.
 */
static void
split_id(CLASS_ID_P id, char **na, char **nb)
{
	*na = DEREF_string(cid_name(id));
	*nb = DEREF_string(cid_name_aux(id));

	crt_file_name = DEREF_string(cid_file(id));
	crt_line_no = DEREF_int(cid_line(id));
}

/*
 * CHECK FOR NAME CLASHES
 *
 * This routine scans through the entire algebra definition checking for
 * name clashes.  Type names are only checked if c is true.
 */
void
check_names(int c)
{
	CLASS_ID_P id;
	char *na, *nb;
	char *empty = "";
	int line = crt_line_no;
	const char *file = crt_file_name;
	all_names = NULL;

	LOOP_PRIMITIVE {
		id = DEREF_ptr(prim_id(CRT_PRIMITIVE));
		split_id(id, &na, &nb);
		if (c) {
			make_name(NAME_TYPE, na, empty, empty);
		}
		make_name(NAME_TYPE_AUX, nb, empty, empty);
	}

	LOOP_IDENTITY {
		id = DEREF_ptr(ident_id(CRT_IDENTITY));
		split_id(id, &na, &nb);
		if (c) {
			make_name(NAME_TYPE, na, empty, empty);
		}
		make_name(NAME_TYPE_AUX, nb, empty, empty);
	}

	LOOP_ENUM {
		id = DEREF_ptr(en_id(CRT_ENUM));
		split_id(id, &na, &nb);
		if (c) {
			make_name(NAME_TYPE, na, empty, empty);
		}
		make_name(NAME_TYPE_AUX, nb, empty, empty);
		LOOP_ENUM_CONST {
			char *ne = DEREF_string(ec_name(CRT_ECONST));
			make_name(NAME_ENUM_CONST, na, ne, empty);
		}
	}

	LOOP_STRUCTURE {
		id = DEREF_ptr(str_id(CRT_STRUCTURE));
		split_id(id, &na, &nb);
		if (c) {
			make_name(NAME_TYPE, na, empty, empty);
		}
		make_name(NAME_TYPE_AUX, nb, empty, empty);
		LOOP_STRUCTURE_COMPONENT {
			char *nc = DEREF_string(cmp_name(CRT_COMPONENT));
			make_name(NAME_STRUCT_CMP, na, nc, empty);
		}
	}

	LOOP_UNION {
		id = DEREF_ptr(un_id(CRT_UNION));
		split_id(id, &na, &nb);
		if (c) {
			make_name(NAME_TYPE, na, empty, empty);
		}
		make_name(NAME_TYPE_AUX, nb, empty, empty);
		LOOP_UNION_COMPONENT {
			char *nc = DEREF_string(cmp_name(CRT_COMPONENT));
			make_name(NAME_UNION_CMP, na, nc, empty);
		}
		LOOP_UNION_FIELD {
			char *nf = DEREF_string(fld_name(CRT_FIELD));
			make_name(NAME_UNION_CMP, na, nf, empty);
			LOOP_FIELD_COMPONENT {
				char *nc = DEREF_string(cmp_name(CRT_COMPONENT));
				make_name(NAME_FIELD_CMP, na, nf, nc);
			}
		}
		LOOP_UNION_MAP {
			char *nm = DEREF_string(map_name(CRT_MAP));
			make_name(NAME_MAP, na, nm, empty);
			LOOP_MAP_ARGUMENT {
				char *np = DEREF_string(arg_name(CRT_ARGUMENT));
				make_name(NAME_MAP_ARG, na, nm, np);
			}
		}
	}

	crt_file_name = file;
	crt_line_no = line;
}


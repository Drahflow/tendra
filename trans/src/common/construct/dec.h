/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONSTRUCT_DEC_H
#define CONSTRUCT_DEC_H

#ifdef TDF_DIAG4
#include <diag4/dg_first.h>
#else
#include <diag3/dg_first.h>
#include <diag3/diaginfo.h>
#endif


/* structure which describes a declaration */
struct dec_t {
	/*
	 * If this is a global declaration this field holds next global
	 * declaration which needs processing. If there is none, it is NULL.
	 */
	struct dec_t *def_next;

	char *dec_id;    /* identifier to be used */
	shape dec_shape; /* shape of the value */
	exp dec_exp;     /* definition or NULL */

	int unit_number;

#ifdef TDF_DIAG4
	struct dg_name_t *dg_name;
#else
	diag_descriptor *diag_info;
#endif

	access acc;

	int index; /* used in inl_norm to hold procedure index number */

#if TRANS_MIPS || TRANS_SPARC || TRANS_POWER || TRANS_ALPHA || TRANS_HPPA
	int sym_number;
#endif

	/* bitfields only after this */

	bool extnamed      :1; /* external */
	bool dec_var       :1; /* this is a variable */
	bool dec_outermost :1; /* this is global */
	bool have_def      :1; /* we have a definition */
	bool processed     :1; /* this exp has been output */
	bool isweak        :1; /* definition is weak */
	bool is_common     :1; /* declaration is common */
	bool has_signature :1; /* declaration has signature */
};

typedef struct dec_t dec;


#endif

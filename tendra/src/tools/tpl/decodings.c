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


#include "config.h"
#include "enc_nos.h"
#include "errors.h"
#include "readstreams.h"
#include "decodings.h"


/* DECODE ACCESS */

unsigned int
d_access(int n)
{
	unsigned int enc = get_basic_int(4, 1);
	switch (enc) {
	case e_access_apply_token:
		consname("access_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("access_apply_token", n + 1);
		    break;
	case e_access_cond:
		consname("access_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("access_cond", n + 1);
		    IGNORE d_bitstream("access_cond", n + 1);
		    break;
	case e_add_accesses:
		consname("add_accesses", n);
		    IGNORE d_access(n + 1);
		    IGNORE d_access(n + 1);
		    break;
	case e_constant:
		consname("constant", n);
		    break;
	case e_long_jump_access:
		consname("long_jump_access", n);
		    break;
	case e_no_other_read:
		consname("no_other_read", n);
		    break;
	case e_no_other_write:
		consname("no_other_write", n);
		    break;
	case e_out_par:
		consname("out_par", n);
		    break;
	case e_preserve:
		consname("preserve", n);
		    break;
	case e_register:
		consname("register", n);
		    break;
	case e_standard_access:
		consname("standard_access", n);
		    break;
	case e_used_as_volatile:
		consname("used_as_volatile", n);
		    break;
	case e_visible:
		consname("visible", n);
		    break;
	default:
		fail("Bad access value, 0", enc);
		break;
	}
	return(enc);
}


/* DECODE OPTIONAL ACCESS */

unsigned int
d_access_option(int n)
{
	unsigned int nl = get_basic_int(1, 0);
	if (nl) {
		IGNORE d_access(n);
	}
	return(nl);
}


/* DECODE AL_TAG */

unsigned int
d_al_tag(int n)
{
	unsigned int enc = get_basic_int(1, 1);
	switch (enc) {
	case e_al_tag_apply_token:
		consname("al_tag_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("al_tag_apply_token", n + 1);
		    break;
	case e_make_al_tag:
		consname("make_al_tag", n);
		    IGNORE d_tdfint(n + 1);
		    break;
	default:
		fail("Bad al_tag value, 1", enc);
		break;
	}
	return(enc);
}


/* DECODE AL_TAGDEF */

unsigned int
d_al_tagdef(int n)
{
	unsigned int enc = get_basic_int(1, 1);
	switch (enc) {
	case e_make_al_tagdef:
		consname("make_al_tagdef", n);
		    IGNORE d_tdfint(n + 1);
		    IGNORE d_alignment(n + 1);
		    break;
	default:
		fail("Bad al_tagdef value, 2", enc);
		break;
	}
	return(enc);
}


/* DECODE SIMPLE AL_TAGDEF LIST */

unsigned int
d_al_tagdef_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_al_tagdef(n + 1);
	}
	return(nl);
}


/* DECODE AL_TAGDEF_PROPS */

unsigned int
d_al_tagdef_props(int n)
{
	    consname("make_al_tagdefs", n);
	    IGNORE d_tdfint(n + 1);
	    IGNORE d_al_tagdef_list(n + 1);
	    return(0);
}


/* DECODE ALIGNMENT */

unsigned int
d_alignment(int n)
{
	unsigned int enc = get_basic_int(4, 1);
	switch (enc) {
	case e_alignment_apply_token:
		consname("alignment_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("alignment_apply_token", n + 1);
		    break;
	case e_alignment_cond:
		consname("alignment_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("alignment_cond", n + 1);
		    IGNORE d_bitstream("alignment_cond", n + 1);
		    break;
	case e_alignment:
		consname("alignment", n);
		    IGNORE d_shape(n + 1);
		    break;
	case e_alloca_alignment:
		consname("alloca_alignment", n);
		    break;
	case e_callees_alignment:
		consname("callees_alignment", n);
		    IGNORE d_bool(n + 1);
		    break;
	case e_callers_alignment:
		consname("callers_alignment", n);
		    IGNORE d_bool(n + 1);
		    break;
	case e_code_alignment:
		consname("code_alignment", n);
		    break;
	case e_locals_alignment:
		consname("locals_alignment", n);
		    break;
	case e_obtain_al_tag:
		consname("obtain_al_tag", n);
		    IGNORE d_al_tag(n + 1);
		    break;
	case e_parameter_alignment:
		consname("parameter_alignment", n);
		    IGNORE d_shape(n + 1);
		    break;
	case e_unite_alignments:
		consname("unite_alignments", n);
		    IGNORE d_alignment(n + 1);
		    IGNORE d_alignment(n + 1);
		    break;
	case e_var_param_alignment:
		consname("var_param_alignment", n);
		    break;
	default:
		fail("Bad alignment value, 3", enc);
		break;
	}
	return(enc);
}


/* DECODE BITFIELD_VARIETY */

unsigned int
d_bitfield_variety(int n)
{
	unsigned int enc = get_basic_int(2, 1);
	switch (enc) {
	case e_bfvar_apply_token:
		consname("bfvar_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("bfvar_apply_token", n + 1);
		    break;
	case e_bfvar_cond:
		consname("bfvar_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("bfvar_cond", n + 1);
		    IGNORE d_bitstream("bfvar_cond", n + 1);
		    break;
	case e_bfvar_bits:
		consname("bfvar_bits", n);
		    IGNORE d_bool(n + 1);
		    IGNORE d_nat(n + 1);
		    break;
	default:
		fail("Bad bitfield_variety value, 4", enc);
		break;
	}
	return(enc);
}


/* DECODE BOOL */

unsigned int
d_bool(int n)
{
	unsigned int enc = get_basic_int(3, 1);
	switch (enc) {
	case e_bool_apply_token:
		consname("bool_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("bool_apply_token", n + 1);
		    break;
	case e_bool_cond:
		consname("bool_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("bool_cond", n + 1);
		    IGNORE d_bitstream("bool_cond", n + 1);
		    break;
	case e_false:
		consname("false", n);
		    break;
	case e_true:
		consname("true", n);
		    break;
	default:
		fail("Bad bool value, 5", enc);
		break;
	}
	return(enc);
}


/* DECODE CALLEES */

unsigned int
d_callees(int n)
{
	unsigned int enc = get_basic_int(2, 1);
	switch (enc) {
	case e_make_callee_list:
		consname("make_callee_list", n);
		    IGNORE d_exp_list(n + 1);
		    break;
	case e_make_dynamic_callees:
		consname("make_dynamic_callees", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_same_callees:
		consname("same_callees", n);
		    break;
	default:
		fail("Bad callees value, 6", enc);
		break;
	}
	return(enc);
}


/* DECODE CAPSULE */

unsigned int
d_capsule(int n)
{
	    consname("make_capsule", n);
	    IGNORE d_tdfident_list(n + 1);
	    IGNORE d_capsule_link_list(n + 1);
	    IGNORE d_extern_link_list(n + 1);
	    IGNORE d_group_list(n + 1);
	    return(0);
}


/* DECODE CAPSULE_LINK */

unsigned int
d_capsule_link(int n)
{
	    consname("make_capsule_link", n);
	    IGNORE d_tdfident(n + 1);
	    IGNORE d_tdfint(n + 1);
	    return(0);
}


/* DECODE SIMPLE CAPSULE_LINK LIST */

unsigned int
d_capsule_link_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_capsule_link(n + 1);
	}
	return(nl);
}


/* DECODE CASELIM */

unsigned int
d_caselim(int n)
{
	    consname("make_caselim", n);
	    IGNORE d_label(n + 1);
	    IGNORE d_signed_nat(n + 1);
	    IGNORE d_signed_nat(n + 1);
	    return(0);
}


/* DECODE CASELIM LIST */

unsigned int
d_caselim_list(int n)
{
	unsigned int nl;
	IGNORE get_basic_int(1, 0);
	nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_caselim(n + 1);
	}
	return(nl);
}


/* DECODE DIAG_DESCRIPTOR */

unsigned int
d_diag_descriptor(int n)
{
	unsigned int enc = get_basic_int(2, 1);
	switch (enc) {
	case e_diag_desc_id:
		consname("diag_desc_id", n);
		    IGNORE d_tdfstring(n + 1);
		    IGNORE d_sourcemark(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_diag_type(n + 1);
		    break;
	case e_diag_desc_struct:
		consname("diag_desc_struct", n);
		    IGNORE d_tdfstring(n + 1);
		    IGNORE d_sourcemark(n + 1);
		    IGNORE d_diag_type(n + 1);
		    break;
	case e_diag_desc_typedef:
		consname("diag_desc_typedef", n);
		    IGNORE d_tdfstring(n + 1);
		    IGNORE d_sourcemark(n + 1);
		    IGNORE d_diag_type(n + 1);
		    break;
	default:
		fail("Bad diag_descriptor value, 7", enc);
		break;
	}
	return(enc);
}


/* DECODE SIMPLE DIAG_DESCRIPTOR LIST */

unsigned int
d_diag_descriptor_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_diag_descriptor(n + 1);
	}
	return(nl);
}


/* DECODE DIAG_FIELD */

unsigned int
d_diag_field(int n)
{
	    consname("make_diag_field", n);
	    IGNORE d_tdfstring(n + 1);
	    IGNORE d_exp(n + 1);
	    IGNORE d_diag_type(n + 1);
	    return(0);
}


/* DECODE DIAG_FIELD LIST */

unsigned int
d_diag_field_list(int n)
{
	unsigned int nl;
	IGNORE get_basic_int(1, 0);
	nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_diag_field(n + 1);
	}
	return(nl);
}


/* DECODE DIAG_TAG */

unsigned int
d_diag_tag(int n)
{
	unsigned int enc = get_basic_int(1, 1);
	switch (enc) {
	case e_make_diag_tag:
		consname("make_diag_tag", n);
		    IGNORE d_tdfint(n + 1);
		    break;
	default:
		fail("Bad diag_tag value, 8", enc);
		break;
	}
	return(enc);
}


/* DECODE DIAG_TAGDEF */

unsigned int
d_diag_tagdef(int n)
{
	unsigned int enc = get_basic_int(1, 1);
	switch (enc) {
	case e_make_diag_tagdef:
		consname("make_diag_tagdef", n);
		    IGNORE d_tdfint(n + 1);
		    IGNORE d_diag_type(n + 1);
		    break;
	default:
		fail("Bad diag_tagdef value, 9", enc);
		break;
	}
	return(enc);
}


/* DECODE SIMPLE DIAG_TAGDEF LIST */

unsigned int
d_diag_tagdef_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_diag_tagdef(n + 1);
	}
	return(nl);
}


/* DECODE DIAG_TQ */

unsigned int
d_diag_tq(int n)
{
	unsigned int enc = get_basic_int(2, 1);
	switch (enc) {
	case e_add_diag_const:
		consname("add_diag_const", n);
		    IGNORE d_diag_tq(n + 1);
		    break;
	case e_add_diag_volatile:
		consname("add_diag_volatile", n);
		    IGNORE d_diag_tq(n + 1);
		    break;
	case e_diag_tq_null:
		consname("diag_tq_null", n);
		    break;
	default:
		fail("Bad diag_tq value, 10", enc);
		break;
	}
	return(enc);
}


/* DECODE DIAG_TYPE */

unsigned int
d_diag_type(int n)
{
	unsigned int enc = get_basic_int(4, 1);
	switch (enc) {
	case e_diag_type_apply_token:
		consname("diag_type_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("diag_type_apply_token", n + 1);
		    break;
	case e_diag_array:
		consname("diag_array", n);
		    IGNORE d_diag_type(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_diag_type(n + 1);
		    break;
	case e_diag_bitfield:
		consname("diag_bitfield", n);
		    IGNORE d_diag_type(n + 1);
		    IGNORE d_nat(n + 1);
		    break;
	case e_diag_enum:
		consname("diag_enum", n);
		    IGNORE d_diag_type(n + 1);
		    IGNORE d_tdfstring(n + 1);
		    IGNORE d_enum_values_list(n + 1);
		    break;
	case e_diag_floating_variety:
		consname("diag_floating_variety", n);
		    IGNORE d_floating_variety(n + 1);
		    break;
	case e_diag_loc:
		consname("diag_loc", n);
		    IGNORE d_diag_type(n + 1);
		    IGNORE d_diag_tq(n + 1);
		    break;
	case e_diag_proc:
		consname("diag_proc", n);
		    IGNORE d_diag_type_list(n + 1);
		    IGNORE d_bool(n + 1);
		    IGNORE d_diag_type(n + 1);
		    break;
	case e_diag_ptr:
		consname("diag_ptr", n);
		    IGNORE d_diag_type(n + 1);
		    IGNORE d_diag_tq(n + 1);
		    break;
	case e_diag_struct:
		consname("diag_struct", n);
		    IGNORE d_shape(n + 1);
		    IGNORE d_tdfstring(n + 1);
		    IGNORE d_diag_field_list(n + 1);
		    break;
	case e_diag_type_null:
		consname("diag_type_null", n);
		    break;
	case e_diag_union:
		consname("diag_union", n);
		    IGNORE d_shape(n + 1);
		    IGNORE d_tdfstring(n + 1);
		    IGNORE d_diag_field_list(n + 1);
		    break;
	case e_diag_variety:
		consname("diag_variety", n);
		    IGNORE d_variety(n + 1);
		    break;
	case e_use_diag_tag:
		consname("use_diag_tag", n);
		    IGNORE d_diag_tag(n + 1);
		    break;
	default:
		fail("Bad diag_type value, 11", enc);
		break;
	}
	return(enc);
}


/* DECODE DIAG_TYPE LIST */

unsigned int
d_diag_type_list(int n)
{
	unsigned int nl;
	IGNORE get_basic_int(1, 0);
	nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_diag_type(n + 1);
	}
	return(nl);
}


/* DECODE DIAG_TYPE_UNIT */

unsigned int
d_diag_type_unit(int n)
{
	    consname("build_diagtype_unit", n);
	    IGNORE d_tdfint(n + 1);
	    IGNORE d_diag_tagdef_list(n + 1);
	    return(0);
}


/* DECODE DIAG_UNIT */

unsigned int
d_diag_unit(int n)
{
	    consname("build_diag_unit", n);
	    IGNORE d_tdfint(n + 1);
	    IGNORE d_diag_descriptor_list(n + 1);
	    return(0);
}


/* DECODE ENUM_VALUES */

unsigned int
d_enum_values(int n)
{
	    consname("make_enum_values", n);
	    IGNORE d_exp(n + 1);
	    IGNORE d_tdfstring(n + 1);
	    return(0);
}


/* DECODE ENUM_VALUES LIST */

unsigned int
d_enum_values_list(int n)
{
	unsigned int nl;
	IGNORE get_basic_int(1, 0);
	nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_enum_values(n + 1);
	}
	return(nl);
}


/* DECODE ERROR_CODE */

unsigned int
d_error_code(int n)
{
	unsigned int enc = get_basic_int(2, 1);
	switch (enc) {
	case e_nil_access:
		consname("nil_access", n);
		    break;
	case e_overflow:
		consname("overflow", n);
		    break;
	case e_stack_overflow:
		consname("stack_overflow", n);
		    break;
	default:
		fail("Bad error_code value, 12", enc);
		break;
	}
	return(enc);
}


/* DECODE ERROR_CODE LIST */

unsigned int
d_error_code_list(int n)
{
	unsigned int nl;
	IGNORE get_basic_int(1, 0);
	nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_error_code(n + 1);
	}
	return(nl);
}


/* DECODE ERROR_TREATMENT */

unsigned int
d_error_treatment(int n)
{
	unsigned int enc = get_basic_int(3, 1);
	switch (enc) {
	case e_errt_apply_token:
		consname("errt_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("errt_apply_token", n + 1);
		    break;
	case e_errt_cond:
		consname("errt_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("errt_cond", n + 1);
		    IGNORE d_bitstream("errt_cond", n + 1);
		    break;
	case e_continue:
		consname("continue", n);
		    break;
	case e_error_jump:
		consname("error_jump", n);
		    IGNORE d_label(n + 1);
		    break;
	case e_trap:
		consname("trap", n);
		    IGNORE d_error_code_list(n + 1);
		    break;
	case e_wrap:
		consname("wrap", n);
		    break;
	case e_impossible:
		consname("impossible", n);
		    break;
	default:
		fail("Bad error_treatment value, 13", enc);
		break;
	}
	return(enc);
}


/* DECODE EXP */

unsigned int
d_exp(int n)
{
	unsigned int enc = get_basic_int(7, 1);
	switch (enc) {
	case e_exp_apply_token:
		consname("exp_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("exp_apply_token", n + 1);
		    break;
	case e_exp_cond:
		consname("exp_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("exp_cond", n + 1);
		    IGNORE d_bitstream("exp_cond", n + 1);
		    break;
	case e_abs:
		consname("abs", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_add_to_ptr:
		consname("add_to_ptr", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_and:
		consname("and", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_apply_proc:
		consname("apply_proc", n);
		    IGNORE d_shape(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp_list(n + 1);
		    IGNORE d_exp_option(n + 1);
		    break;
	case e_apply_general_proc:
		consname("apply_general_proc", n);
		    IGNORE d_shape(n + 1);
		    IGNORE d_procprops_option(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_otagexp_list(n + 1);
		    IGNORE d_callees(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_assign:
		consname("assign", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_assign_with_mode:
		consname("assign_with_mode", n);
		    IGNORE d_transfer_mode(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_bitfield_assign:
		consname("bitfield_assign", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_bitfield_assign_with_mode:
		consname("bitfield_assign_with_mode", n);
		    IGNORE d_transfer_mode(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_bitfield_contents:
		consname("bitfield_contents", n);
		    IGNORE d_bitfield_variety(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_bitfield_contents_with_mode:
		consname("bitfield_contents_with_mode", n);
		    IGNORE d_transfer_mode(n + 1);
		    IGNORE d_bitfield_variety(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_case:
		consname("case", n);
		    IGNORE d_bool(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_caselim_list(n + 1);
		    break;
	case e_change_bitfield_to_int:
		consname("change_bitfield_to_int", n);
		    IGNORE d_variety(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_change_floating_variety:
		consname("change_floating_variety", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_floating_variety(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_change_variety:
		consname("change_variety", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_variety(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_change_int_to_bitfield:
		consname("change_int_to_bitfield", n);
		    IGNORE d_bitfield_variety(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_complex_conjugate:
		consname("complex_conjugate", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_component:
		consname("component", n);
		    IGNORE d_shape(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_concat_nof:
		consname("concat_nof", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_conditional:
		consname("conditional", n);
		    IGNORE d_label(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_contents:
		consname("contents", n);
		    IGNORE d_shape(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_contents_with_mode:
		consname("contents_with_mode", n);
		    IGNORE d_transfer_mode(n + 1);
		    IGNORE d_shape(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_current_env:
		consname("current_env", n);
		    break;
	case e_div0:
		consname("div0", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_div1:
		consname("div1", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_div2:
		consname("div2", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_env_offset:
		consname("env_offset", n);
		    IGNORE d_alignment(n + 1);
		    IGNORE d_alignment(n + 1);
		    IGNORE d_tag(n + 1);
		    break;
	case e_env_size:
		consname("env_size", n);
		    IGNORE d_tag(n + 1);
		    break;
	case e_fail_installer:
		consname("fail_installer", n);
		    IGNORE d_string(n + 1);
		    break;
	case e_float_int:
		consname("float_int", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_floating_variety(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_floating_abs:
		consname("floating_abs", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_floating_div:
		consname("floating_div", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_floating_minus:
		consname("floating_minus", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_floating_maximum:
		consname("floating_maximum", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_floating_minimum:
		consname("floating_minimum", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_floating_mult:
		consname("floating_mult", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp_list(n + 1);
		    break;
	case e_floating_negate:
		consname("floating_negate", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_floating_plus:
		consname("floating_plus", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp_list(n + 1);
		    break;
	case e_floating_power:
		consname("floating_power", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_floating_test:
		consname("floating_test", n);
		    IGNORE d_nat_option(n + 1);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_ntest(n + 1);
		    IGNORE d_label(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_goto:
		consname("goto", n);
		    IGNORE d_label(n + 1);
		    break;
	case e_goto_local_lv:
		consname("goto_local_lv", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_identify:
		consname("identify", n);
		    IGNORE d_access_option(n + 1);
		    IGNORE d_tag(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_ignorable:
		consname("ignorable", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_imaginary_part:
		consname("imaginary_part", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_initial_value:
		consname("initial_value", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_integer_test:
		consname("integer_test", n);
		    IGNORE d_nat_option(n + 1);
		    IGNORE d_ntest(n + 1);
		    IGNORE d_label(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_labelled:
		consname("labelled", n);
		    IGNORE d_label_list(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp_list(n + 1);
		    break;
	case e_last_local:
		consname("last_local", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_local_alloc:
		consname("local_alloc", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_local_alloc_check:
		consname("local_alloc_check", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_local_free:
		consname("local_free", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_local_free_all:
		consname("local_free_all", n);
		    break;
	case e_long_jump:
		consname("long_jump", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_make_complex:
		consname("make_complex", n);
		    IGNORE d_floating_variety(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_make_compound:
		consname("make_compound", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp_list(n + 1);
		    break;
	case e_make_floating:
		consname("make_floating", n);
		    IGNORE d_floating_variety(n + 1);
		    IGNORE d_rounding_mode(n + 1);
		    IGNORE d_bool(n + 1);
		    IGNORE d_string(n + 1);
		    IGNORE d_nat(n + 1);
		    IGNORE d_signed_nat(n + 1);
		    break;
	case e_make_general_proc:
		consname("make_general_proc", n);
		    IGNORE d_shape(n + 1);
		    IGNORE d_procprops_option(n + 1);
		    IGNORE d_tagshacc_list(n + 1);
		    IGNORE d_tagshacc_list(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_make_int:
		consname("make_int", n);
		    IGNORE d_variety(n + 1);
		    IGNORE d_signed_nat(n + 1);
		    break;
	case e_make_local_lv:
		consname("make_local_lv", n);
		    IGNORE d_label(n + 1);
		    break;
	case e_make_nof:
		consname("make_nof", n);
		    IGNORE d_exp_list(n + 1);
		    break;
	case e_make_nof_int:
		consname("make_nof_int", n);
		    IGNORE d_variety(n + 1);
		    IGNORE d_string(n + 1);
		    break;
	case e_make_null_local_lv:
		consname("make_null_local_lv", n);
		    break;
	case e_make_null_proc:
		consname("make_null_proc", n);
		    break;
	case e_make_null_ptr:
		consname("make_null_ptr", n);
		    IGNORE d_alignment(n + 1);
		    break;
	case e_make_proc:
		consname("make_proc", n);
		    IGNORE d_shape(n + 1);
		    IGNORE d_tagshacc_list(n + 1);
		    IGNORE d_tagacc_option(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_make_stack_limit:
		consname("make_stack_limit", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_make_top:
		consname("make_top", n);
		    break;
	case e_make_value:
		consname("make_value", n);
		    IGNORE d_shape(n + 1);
		    break;
	case e_maximum:
		consname("maximum", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_minimum:
		consname("minimum", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_minus:
		consname("minus", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_move_some:
		consname("move_some", n);
		    IGNORE d_transfer_mode(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_mult:
		consname("mult", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_n_copies:
		consname("n_copies", n);
		    IGNORE d_nat(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_negate:
		consname("negate", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_not:
		consname("not", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_obtain_tag:
		consname("obtain_tag", n);
		    IGNORE d_tag(n + 1);
		    break;
	case e_offset_add:
		consname("offset_add", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_offset_div:
		consname("offset_div", n);
		    IGNORE d_variety(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_offset_div_by_int:
		consname("offset_div_by_int", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_offset_max:
		consname("offset_max", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_offset_mult:
		consname("offset_mult", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_offset_negate:
		consname("offset_negate", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_offset_pad:
		consname("offset_pad", n);
		    IGNORE d_alignment(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_offset_subtract:
		consname("offset_subtract", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_offset_test:
		consname("offset_test", n);
		    IGNORE d_nat_option(n + 1);
		    IGNORE d_ntest(n + 1);
		    IGNORE d_label(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_offset_zero:
		consname("offset_zero", n);
		    IGNORE d_alignment(n + 1);
		    break;
	case e_or:
		consname("or", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_plus:
		consname("plus", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_pointer_test:
		consname("pointer_test", n);
		    IGNORE d_nat_option(n + 1);
		    IGNORE d_ntest(n + 1);
		    IGNORE d_label(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_power:
		consname("power", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_proc_test:
		consname("proc_test", n);
		    IGNORE d_nat_option(n + 1);
		    IGNORE d_ntest(n + 1);
		    IGNORE d_label(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_profile:
		consname("profile", n);
		    IGNORE d_nat(n + 1);
		    break;
	case e_real_part:
		consname("real_part", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_rem0:
		consname("rem0", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_rem1:
		consname("rem1", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_rem2:
		consname("rem2", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_repeat:
		consname("repeat", n);
		    IGNORE d_label(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_return:
		consname("return", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_return_to_label:
		consname("return_to_label", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_round_with_mode:
		consname("round_with_mode", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_rounding_mode(n + 1);
		    IGNORE d_variety(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_rotate_left:
		consname("rotate_left", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_rotate_right:
		consname("rotate_right", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_sequence:
		consname("sequence", n);
		    IGNORE d_exp_list(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_set_stack_limit:
		consname("set_stack_limit", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_shape_offset:
		consname("shape_offset", n);
		    IGNORE d_shape(n + 1);
		    break;
	case e_shift_left:
		consname("shift_left", n);
		    IGNORE d_error_treatment(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_shift_right:
		consname("shift_right", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_subtract_ptrs:
		consname("subtract_ptrs", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_tail_call:
		consname("tail_call", n);
		    IGNORE d_procprops_option(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_callees(n + 1);
		    break;
	case e_untidy_return:
		consname("untidy_return", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_variable:
		consname("variable", n);
		    IGNORE d_access_option(n + 1);
		    IGNORE d_tag(n + 1);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_xor:
		consname("xor", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	default:
		fail("Bad exp value, 14", enc);
		break;
	}
	return(enc);
}


/* DECODE EXP LIST */

unsigned int
d_exp_list(int n)
{
	unsigned int nl;
	IGNORE get_basic_int(1, 0);
	nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_exp(n + 1);
	}
	return(nl);
}


/* DECODE OPTIONAL EXP */

unsigned int
d_exp_option(int n)
{
	unsigned int nl = get_basic_int(1, 0);
	if (nl) {
		IGNORE d_exp(n);
	}
	return(nl);
}


/* DECODE EXTERN_LINK */

unsigned int
d_extern_link(int n)
{
	    consname("make_extern_link", n);
	    IGNORE d_linkextern_list(n + 1);
	    return(0);
}


/* DECODE SIMPLE EXTERN_LINK LIST */

unsigned int
d_extern_link_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_extern_link(n + 1);
	}
	return(nl);
}


/* DECODE EXTERNAL */

unsigned int
d_external(int n)
{
	unsigned int enc = get_basic_int(2, 1);
	switch (enc) {
	case e_string_extern:
		consname("string_extern", n);
		    IGNORE d_tdfident(n + 1);
		    break;
	case e_unique_extern:
		consname("unique_extern", n);
		    IGNORE d_unique(n + 1);
		    break;
	case e_chain_extern:
		consname("chain_extern", n);
		    IGNORE d_tdfident(n + 1);
		    IGNORE d_tdfint(n + 1);
		    break;
	default:
		fail("Bad external value, 15", enc);
		break;
	}
	return(enc);
}


/* DECODE FILENAME */

unsigned int
d_filename(int n)
{
	unsigned int enc = get_basic_int(2, 1);
	switch (enc) {
	case e_filename_apply_token:
		consname("filename_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("filename_apply_token", n + 1);
		    break;
	case e_make_filename:
		consname("make_filename", n);
		    IGNORE d_nat(n + 1);
		    IGNORE d_tdfstring(n + 1);
		    IGNORE d_tdfstring(n + 1);
		    break;
	default:
		fail("Bad filename value, 16", enc);
		break;
	}
	return(enc);
}


/* DECODE FLOATING_VARIETY */

unsigned int
d_floating_variety(int n)
{
	unsigned int enc = get_basic_int(3, 1);
	switch (enc) {
	case e_flvar_apply_token:
		consname("flvar_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("flvar_apply_token", n + 1);
		    break;
	case e_flvar_cond:
		consname("flvar_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("flvar_cond", n + 1);
		    IGNORE d_bitstream("flvar_cond", n + 1);
		    break;
	case e_flvar_parms:
		consname("flvar_parms", n);
		    IGNORE d_nat(n + 1);
		    IGNORE d_nat(n + 1);
		    IGNORE d_nat(n + 1);
		    IGNORE d_nat(n + 1);
		    break;
	case e_complex_parms:
		consname("complex_parms", n);
		    IGNORE d_nat(n + 1);
		    IGNORE d_nat(n + 1);
		    IGNORE d_nat(n + 1);
		    IGNORE d_nat(n + 1);
		    break;
	case e_float_of_complex:
		consname("float_of_complex", n);
		    IGNORE d_shape(n + 1);
		    break;
	case e_complex_of_float:
		consname("complex_of_float", n);
		    IGNORE d_shape(n + 1);
		    break;
	default:
		fail("Bad floating_variety value, 17", enc);
		break;
	}
	return(enc);
}


/* DECODE GROUP */

unsigned int
d_group(int n)
{
	    consname("make_group", n);
	    IGNORE d_unit_list(n + 1);
	    return(0);
}


/* DECODE SIMPLE GROUP LIST */

unsigned int
d_group_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_group(n + 1);
	}
	return(nl);
}


/* DECODE LABEL */

unsigned int
d_label(int n)
{
	unsigned int enc = get_basic_int(1, 1);
	switch (enc) {
	case e_label_apply_token:
		consname("label_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("label_apply_token", n + 1);
		    break;
	case e_make_label:
		consname("make_label", n);
		    IGNORE d_tdfint(n + 1);
		    break;
	default:
		fail("Bad label value, 18", enc);
		break;
	}
	return(enc);
}


/* DECODE LABEL LIST */

unsigned int
d_label_list(int n)
{
	unsigned int nl;
	IGNORE get_basic_int(1, 0);
	nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_label(n + 1);
	}
	return(nl);
}


/* DECODE LINK */

unsigned int
d_link(int n)
{
	    consname("make_link", n);
	    IGNORE d_tdfint(n + 1);
	    IGNORE d_tdfint(n + 1);
	    return(0);
}


/* DECODE SIMPLE LINK LIST */

unsigned int
d_link_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_link(n + 1);
	}
	return(nl);
}


/* DECODE LINKEXTERN */

unsigned int
d_linkextern(int n)
{
	    consname("make_linkextern", n);
	    IGNORE d_tdfint(n + 1);
	    IGNORE d_external(n + 1);
	    return(0);
}


/* DECODE SIMPLE LINKEXTERN LIST */

unsigned int
d_linkextern_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_linkextern(n + 1);
	}
	return(nl);
}


/* DECODE LINKINFO */

unsigned int
d_linkinfo(int n)
{
	unsigned int enc = get_basic_int(2, 1);
	switch (enc) {
	case e_static_name_def:
		consname("static_name_def", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_tdfstring(n + 1);
		    break;
	case e_make_comment:
		consname("make_comment", n);
		    IGNORE d_tdfstring(n + 1);
		    break;
	case e_make_weak_defn:
		consname("make_weak_defn", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_make_weak_symbol:
		consname("make_weak_symbol", n);
		    IGNORE d_tdfstring(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	default:
		fail("Bad linkinfo value, 19", enc);
		break;
	}
	return(enc);
}


/* DECODE SIMPLE LINKINFO LIST */

unsigned int
d_linkinfo_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_linkinfo(n + 1);
	}
	return(nl);
}


/* DECODE LINKINFO_PROPS */

unsigned int
d_linkinfo_props(int n)
{
	    consname("make_linkinfos", n);
	    IGNORE d_tdfint(n + 1);
	    IGNORE d_linkinfo_list(n + 1);
	    return(0);
}


/* DECODE LINKS */

unsigned int
d_links(int n)
{
	    consname("make_links", n);
	    IGNORE d_link_list(n + 1);
	    return(0);
}


/* DECODE SIMPLE LINKS LIST */

unsigned int
d_links_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_links(n + 1);
	}
	return(nl);
}


/* DECODE NAT */

unsigned int
d_nat(int n)
{
	unsigned int enc = get_basic_int(3, 1);
	switch (enc) {
	case e_nat_apply_token:
		consname("nat_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("nat_apply_token", n + 1);
		    break;
	case e_nat_cond:
		consname("nat_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("nat_cond", n + 1);
		    IGNORE d_bitstream("nat_cond", n + 1);
		    break;
	case e_computed_nat:
		consname("computed_nat", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_error_val:
		consname("error_val", n);
		    IGNORE d_error_code(n + 1);
		    break;
	case e_make_nat:
		consname("make_nat", n);
		    IGNORE d_tdfint(n + 1);
		    break;
	default:
		fail("Bad nat value, 20", enc);
		break;
	}
	return(enc);
}


/* DECODE OPTIONAL NAT */

unsigned int
d_nat_option(int n)
{
	unsigned int nl = get_basic_int(1, 0);
	if (nl) {
		IGNORE d_nat(n);
	}
	return(nl);
}


/* DECODE NTEST */

unsigned int
d_ntest(int n)
{
	unsigned int enc = get_basic_int(4, 1);
	switch (enc) {
	case e_ntest_apply_token:
		consname("ntest_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("ntest_apply_token", n + 1);
		    break;
	case e_ntest_cond:
		consname("ntest_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("ntest_cond", n + 1);
		    IGNORE d_bitstream("ntest_cond", n + 1);
		    break;
	case e_equal:
		consname("equal", n);
		    break;
	case e_greater_than:
		consname("greater_than", n);
		    break;
	case e_greater_than_or_equal:
		consname("greater_than_or_equal", n);
		    break;
	case e_less_than:
		consname("less_than", n);
		    break;
	case e_less_than_or_equal:
		consname("less_than_or_equal", n);
		    break;
	case e_not_equal:
		consname("not_equal", n);
		    break;
	case e_not_greater_than:
		consname("not_greater_than", n);
		    break;
	case e_not_greater_than_or_equal:
		consname("not_greater_than_or_equal", n);
		    break;
	case e_not_less_than:
		consname("not_less_than", n);
		    break;
	case e_not_less_than_or_equal:
		consname("not_less_than_or_equal", n);
		    break;
	case e_less_than_or_greater_than:
		consname("less_than_or_greater_than", n);
		    break;
	case e_not_less_than_and_not_greater_than:
		consname("not_less_than_and_not_greater_than", n);
		    break;
	case e_comparable:
		consname("comparable", n);
		    break;
	case e_not_comparable:
		consname("not_comparable", n);
		    break;
	default:
		fail("Bad ntest value, 21", enc);
		break;
	}
	return(enc);
}


/* DECODE OTAGEXP */

unsigned int
d_otagexp(int n)
{
	    consname("make_otagexp", n);
	    IGNORE d_tag_option(n + 1);
	    IGNORE d_exp(n + 1);
	    return(0);
}


/* DECODE OTAGEXP LIST */

unsigned int
d_otagexp_list(int n)
{
	unsigned int nl;
	IGNORE get_basic_int(1, 0);
	nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_otagexp(n + 1);
	}
	return(nl);
}


/* DECODE PROCPROPS */

unsigned int
d_procprops(int n)
{
	unsigned int enc = get_basic_int(4, 1);
	switch (enc) {
	case e_procprops_apply_token:
		consname("procprops_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("procprops_apply_token", n + 1);
		    break;
	case e_procprops_cond:
		consname("procprops_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("procprops_cond", n + 1);
		    IGNORE d_bitstream("procprops_cond", n + 1);
		    break;
	case e_add_procprops:
		consname("add_procprops", n);
		    IGNORE d_procprops(n + 1);
		    IGNORE d_procprops(n + 1);
		    break;
	case e_check_stack:
		consname("check_stack", n);
		    break;
	case e_inline:
		consname("inline", n);
		    break;
	case e_no_long_jump_dest:
		consname("no_long_jump_dest", n);
		    break;
	case e_untidy:
		consname("untidy", n);
		    break;
	case e_var_callees:
		consname("var_callees", n);
		    break;
	case e_var_callers:
		consname("var_callers", n);
		    break;
	default:
		fail("Bad procprops value, 22", enc);
		break;
	}
	return(enc);
}


/* DECODE OPTIONAL PROCPROPS */

unsigned int
d_procprops_option(int n)
{
	unsigned int nl = get_basic_int(1, 0);
	if (nl) {
		IGNORE d_procprops(n);
	}
	return(nl);
}


/* DECODE ROUNDING_MODE */

unsigned int
d_rounding_mode(int n)
{
	unsigned int enc = get_basic_int(3, 1);
	switch (enc) {
	case e_rounding_mode_apply_token:
		consname("rounding_mode_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("rounding_mode_apply_token", n + 1);
		    break;
	case e_rounding_mode_cond:
		consname("rounding_mode_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("rounding_mode_cond", n + 1);
		    IGNORE d_bitstream("rounding_mode_cond", n + 1);
		    break;
	case e_round_as_state:
		consname("round_as_state", n);
		    break;
	case e_to_nearest:
		consname("to_nearest", n);
		    break;
	case e_toward_larger:
		consname("toward_larger", n);
		    break;
	case e_toward_smaller:
		consname("toward_smaller", n);
		    break;
	case e_toward_zero:
		consname("toward_zero", n);
		    break;
	default:
		fail("Bad rounding_mode value, 23", enc);
		break;
	}
	return(enc);
}


/* DECODE SHAPE */

unsigned int
d_shape(int n)
{
	unsigned int enc = get_basic_int(4, 1);
	switch (enc) {
	case e_shape_apply_token:
		consname("shape_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("shape_apply_token", n + 1);
		    break;
	case e_shape_cond:
		consname("shape_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("shape_cond", n + 1);
		    IGNORE d_bitstream("shape_cond", n + 1);
		    break;
	case e_bitfield:
		consname("bitfield", n);
		    IGNORE d_bitfield_variety(n + 1);
		    break;
	case e_bottom:
		consname("bottom", n);
		    break;
	case e_compound:
		consname("compound", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_floating:
		consname("floating", n);
		    IGNORE d_floating_variety(n + 1);
		    break;
	case e_integer:
		consname("integer", n);
		    IGNORE d_variety(n + 1);
		    break;
	case e_nof:
		consname("nof", n);
		    IGNORE d_nat(n + 1);
		    IGNORE d_shape(n + 1);
		    break;
	case e_offset:
		consname("offset", n);
		    IGNORE d_alignment(n + 1);
		    IGNORE d_alignment(n + 1);
		    break;
	case e_pointer:
		consname("pointer", n);
		    IGNORE d_alignment(n + 1);
		    break;
	case e_proc:
		consname("proc", n);
		    break;
	case e_top:
		consname("top", n);
		    break;
	default:
		fail("Bad shape value, 24", enc);
		break;
	}
	return(enc);
}


/* DECODE SIGNED_NAT */

unsigned int
d_signed_nat(int n)
{
	unsigned int enc = get_basic_int(3, 1);
	switch (enc) {
	case e_signed_nat_apply_token:
		consname("signed_nat_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("signed_nat_apply_token", n + 1);
		    break;
	case e_signed_nat_cond:
		consname("signed_nat_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("signed_nat_cond", n + 1);
		    IGNORE d_bitstream("signed_nat_cond", n + 1);
		    break;
	case e_computed_signed_nat:
		consname("computed_signed_nat", n);
		    IGNORE d_exp(n + 1);
		    break;
	case e_make_signed_nat:
		consname("make_signed_nat", n);
		    IGNORE d_tdfbool(n + 1);
		    IGNORE d_tdfint(n + 1);
		    break;
	case e_snat_from_nat:
		consname("snat_from_nat", n);
		    IGNORE d_bool(n + 1);
		    IGNORE d_nat(n + 1);
		    break;
	default:
		fail("Bad signed_nat value, 25", enc);
		break;
	}
	return(enc);
}


/* DECODE SORTNAME */

unsigned int
d_sortname(int n)
{
	unsigned int enc = get_basic_int(5, 1);
	switch (enc) {
	case e_access:
		consname("access", n);
		    break;
	case e_al_tag:
		consname("al_tag", n);
		    break;
	case e_alignment_sort:
		consname("alignment_sort", n);
		    break;
	case e_bitfield_variety:
		consname("bitfield_variety", n);
		    break;
	case e_bool:
		consname("bool", n);
		    break;
	case e_error_treatment:
		consname("error_treatment", n);
		    break;
	case e_exp:
		consname("exp", n);
		    break;
	case e_floating_variety:
		consname("floating_variety", n);
		    break;
	case e_foreign_sort:
		consname("foreign_sort", n);
		    IGNORE d_string(n + 1);
		    break;
	case e_label:
		consname("label", n);
		    break;
	case e_nat:
		consname("nat", n);
		    break;
	case e_ntest:
		consname("ntest", n);
		    break;
	case e_procprops:
		consname("procprops", n);
		    break;
	case e_rounding_mode:
		consname("rounding_mode", n);
		    break;
	case e_shape:
		consname("shape", n);
		    break;
	case e_signed_nat:
		consname("signed_nat", n);
		    break;
	case e_string:
		consname("string", n);
		    break;
	case e_tag:
		consname("tag", n);
		    break;
	case e_transfer_mode:
		consname("transfer_mode", n);
		    break;
	case e_token:
		consname("token", n);
		    IGNORE d_sortname(n + 1);
		    IGNORE d_sortname_list(n + 1);
		    break;
	case e_variety:
		consname("variety", n);
		    break;
	default:
		fail("Bad sortname value, 26", enc);
		break;
	}
	return(enc);
}


/* DECODE SORTNAME LIST */

unsigned int
d_sortname_list(int n)
{
	unsigned int nl;
	IGNORE get_basic_int(1, 0);
	nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_sortname(n + 1);
	}
	return(nl);
}


/* DECODE SOURCEMARK */

unsigned int
d_sourcemark(int n)
{
	unsigned int enc = get_basic_int(1, 1);
	switch (enc) {
	case e_make_sourcemark:
		consname("make_sourcemark", n);
		    IGNORE d_filename(n + 1);
		    IGNORE d_nat(n + 1);
		    IGNORE d_nat(n + 1);
		    break;
	default:
		fail("Bad sourcemark value, 27", enc);
		break;
	}
	return(enc);
}


/* DECODE STRING */

unsigned int
d_string(int n)
{
	unsigned int enc = get_basic_int(3, 1);
	switch (enc) {
	case e_string_apply_token:
		consname("string_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("string_apply_token", n + 1);
		    break;
	case e_string_cond:
		consname("string_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("string_cond", n + 1);
		    IGNORE d_bitstream("string_cond", n + 1);
		    break;
	case e_concat_string:
		consname("concat_string", n);
		    IGNORE d_string(n + 1);
		    IGNORE d_string(n + 1);
		    break;
	case e_make_string:
		consname("make_string", n);
		    IGNORE d_tdfstring(n + 1);
		    break;
	default:
		fail("Bad string value, 28", enc);
		break;
	}
	return(enc);
}


/* DECODE OPTIONAL STRING */

unsigned int
d_string_option(int n)
{
	unsigned int nl = get_basic_int(1, 0);
	if (nl) {
		IGNORE d_string(n);
	}
	return(nl);
}


/* DECODE TAG */

unsigned int
d_tag(int n)
{
	unsigned int enc = get_basic_int(1, 1);
	switch (enc) {
	case e_tag_apply_token:
		consname("tag_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("tag_apply_token", n + 1);
		    break;
	case e_make_tag:
		consname("make_tag", n);
		    IGNORE d_tdfint(n + 1);
		    break;
	default:
		fail("Bad tag value, 29", enc);
		break;
	}
	return(enc);
}


/* DECODE OPTIONAL TAG */

unsigned int
d_tag_option(int n)
{
	unsigned int nl = get_basic_int(1, 0);
	if (nl) {
		IGNORE d_tag(n);
	}
	return(nl);
}


/* DECODE TAGACC */

unsigned int
d_tagacc(int n)
{
	    consname("make_tagacc", n);
	    IGNORE d_tag(n + 1);
	    IGNORE d_access_option(n + 1);
	    return(0);
}


/* DECODE OPTIONAL TAGACC */

unsigned int
d_tagacc_option(int n)
{
	unsigned int nl = get_basic_int(1, 0);
	if (nl) {
		IGNORE d_tagacc(n);
	}
	return(nl);
}


/* DECODE TAGDEC */

unsigned int
d_tagdec(int n)
{
	unsigned int enc = get_basic_int(2, 1);
	switch (enc) {
	case e_make_id_tagdec:
		consname("make_id_tagdec", n);
		    IGNORE d_tdfint(n + 1);
		    IGNORE d_access_option(n + 1);
		    IGNORE d_string_option(n + 1);
		    IGNORE d_shape(n + 1);
		    break;
	case e_make_var_tagdec:
		consname("make_var_tagdec", n);
		    IGNORE d_tdfint(n + 1);
		    IGNORE d_access_option(n + 1);
		    IGNORE d_string_option(n + 1);
		    IGNORE d_shape(n + 1);
		    break;
	case e_common_tagdec:
		consname("common_tagdec", n);
		    IGNORE d_tdfint(n + 1);
		    IGNORE d_access_option(n + 1);
		    IGNORE d_string_option(n + 1);
		    IGNORE d_shape(n + 1);
		    break;
	default:
		fail("Bad tagdec value, 30", enc);
		break;
	}
	return(enc);
}


/* DECODE SIMPLE TAGDEC LIST */

unsigned int
d_tagdec_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_tagdec(n + 1);
	}
	return(nl);
}


/* DECODE TAGDEC_PROPS */

unsigned int
d_tagdec_props(int n)
{
	    consname("make_tagdecs", n);
	    IGNORE d_tdfint(n + 1);
	    IGNORE d_tagdec_list(n + 1);
	    return(0);
}


/* DECODE TAGDEF */

unsigned int
d_tagdef(int n)
{
	unsigned int enc = get_basic_int(2, 1);
	switch (enc) {
	case e_make_id_tagdef:
		consname("make_id_tagdef", n);
		    IGNORE d_tdfint(n + 1);
		    IGNORE d_string_option(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_make_var_tagdef:
		consname("make_var_tagdef", n);
		    IGNORE d_tdfint(n + 1);
		    IGNORE d_access_option(n + 1);
		    IGNORE d_string_option(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	case e_common_tagdef:
		consname("common_tagdef", n);
		    IGNORE d_tdfint(n + 1);
		    IGNORE d_access_option(n + 1);
		    IGNORE d_string_option(n + 1);
		    IGNORE d_exp(n + 1);
		    break;
	default:
		fail("Bad tagdef value, 31", enc);
		break;
	}
	return(enc);
}


/* DECODE SIMPLE TAGDEF LIST */

unsigned int
d_tagdef_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_tagdef(n + 1);
	}
	return(nl);
}


/* DECODE TAGDEF_PROPS */

unsigned int
d_tagdef_props(int n)
{
	    consname("make_tagdefs", n);
	    IGNORE d_tdfint(n + 1);
	    IGNORE d_tagdef_list(n + 1);
	    return(0);
}


/* DECODE TAGSHACC */

unsigned int
d_tagshacc(int n)
{
	    consname("make_tagshacc", n);
	    IGNORE d_shape(n + 1);
	    IGNORE d_access_option(n + 1);
	    IGNORE d_tag(n + 1);
	    return(0);
}


/* DECODE TAGSHACC LIST */

unsigned int
d_tagshacc_list(int n)
{
	unsigned int nl;
	IGNORE get_basic_int(1, 0);
	nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_tagshacc(n + 1);
	}
	return(nl);
}


/* DECODE SIMPLE TDFIDENT LIST */

unsigned int
d_tdfident_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_tdfident(n + 1);
	}
	return(nl);
}


/* DECODE SIMPLE TDFINT LIST */

unsigned int
d_tdfint_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_tdfint(n + 1);
	}
	return(nl);
}


/* DECODE TOKDEC */

unsigned int
d_tokdec(int n)
{
	unsigned int enc = get_basic_int(1, 1);
	switch (enc) {
	case e_make_tokdec:
		consname("make_tokdec", n);
		    IGNORE d_tdfint(n + 1);
		    IGNORE d_string_option(n + 1);
		    IGNORE d_sortname(n + 1);
		    break;
	default:
		fail("Bad tokdec value, 32", enc);
		break;
	}
	return(enc);
}


/* DECODE SIMPLE TOKDEC LIST */

unsigned int
d_tokdec_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_tokdec(n + 1);
	}
	return(nl);
}


/* DECODE TOKDEC_PROPS */

unsigned int
d_tokdec_props(int n)
{
	    consname("make_tokdecs", n);
	    IGNORE d_tokdec_list(n + 1);
	    return(0);
}


/* DECODE TOKDEF */

unsigned int
d_tokdef(int n)
{
	unsigned int enc = get_basic_int(1, 1);
	switch (enc) {
	case e_make_tokdef:
		consname("make_tokdef", n);
		    IGNORE d_tdfint(n + 1);
		    IGNORE d_string_option(n + 1);
		    IGNORE d_bitstream("make_tokdef", n + 1);
		    break;
	default:
		fail("Bad tokdef value, 33", enc);
		break;
	}
	return(enc);
}


/* DECODE SIMPLE TOKDEF LIST */

unsigned int
d_tokdef_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_tokdef(n + 1);
	}
	return(nl);
}


/* DECODE TOKDEF_PROPS */

unsigned int
d_tokdef_props(int n)
{
	    consname("make_tokdefs", n);
	    IGNORE d_tdfint(n + 1);
	    IGNORE d_tokdef_list(n + 1);
	    return(0);
}


/* DECODE TOKEN */

unsigned int
d_token(int n)
{
	unsigned int enc = get_basic_int(2, 1);
	switch (enc) {
	case e_token_apply_token:
		consname("token_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("token_apply_token", n + 1);
		    break;
	case e_make_tok:
		consname("make_tok", n);
		    IGNORE d_tdfint(n + 1);
		    break;
	case e_use_tokdef:
		consname("use_tokdef", n);
		    IGNORE d_bitstream("use_tokdef", n + 1);
		    break;
	default:
		fail("Bad token value, 34", enc);
		break;
	}
	return(enc);
}


/* DECODE TOKEN_DEFN */

unsigned int
d_token_defn(int n)
{
	unsigned int enc = get_basic_int(1, 1);
	switch (enc) {
	case e_token_definition:
		consname("token_definition", n);
		    IGNORE d_sortname(n + 1);
		    IGNORE d_tokformals_list(n + 1);
		    break;
	default:
		fail("Bad token_defn value, 35", enc);
		break;
	}
	return(enc);
}


/* DECODE TOKFORMALS */

unsigned int
d_tokformals(int n)
{
	    consname("make_tokformals", n);
	    IGNORE d_sortname(n + 1);
	    IGNORE d_tdfint(n + 1);
	    return(0);
}


/* DECODE TOKFORMALS LIST */

unsigned int
d_tokformals_list(int n)
{
	unsigned int nl;
	IGNORE get_basic_int(1, 0);
	nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_tokformals(n + 1);
	}
	return(nl);
}


/* DECODE TRANSFER_MODE */

unsigned int
d_transfer_mode(int n)
{
	unsigned int enc = get_basic_int(3, 1);
	switch (enc) {
	case e_transfer_mode_apply_token:
		consname("transfer_mode_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("transfer_mode_apply_token", n + 1);
		    break;
	case e_transfer_mode_cond:
		consname("transfer_mode_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("transfer_mode_cond", n + 1);
		    IGNORE d_bitstream("transfer_mode_cond", n + 1);
		    break;
	case e_add_modes:
		consname("add_modes", n);
		    IGNORE d_transfer_mode(n + 1);
		    IGNORE d_transfer_mode(n + 1);
		    break;
	case e_overlap:
		consname("overlap", n);
		    break;
	case e_standard_transfer_mode:
		consname("standard_transfer_mode", n);
		    break;
	case e_trap_on_nil:
		consname("trap_on_nil", n);
		    break;
	case e_volatile:
		consname("volatile", n);
		    break;
	case e_complete:
		consname("complete", n);
		    break;
	default:
		fail("Bad transfer_mode value, 36", enc);
		break;
	}
	return(enc);
}


/* DECODE UNIQUE */

unsigned int
d_unique(int n)
{
	    consname("make_unique", n);
	    IGNORE d_tdfident_list(n + 1);
	    return(0);
}


/* DECODE UNIT */

unsigned int
d_unit(int n)
{
	    consname("make_unit", n);
	    IGNORE d_tdfint_list(n + 1);
	    IGNORE d_links_list(n + 1);
	    IGNORE d_bytestream(n + 1);
	    return(0);
}


/* DECODE SIMPLE UNIT LIST */

unsigned int
d_unit_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_unit(n + 1);
	}
	return(nl);
}


/* DECODE VARIETY */

unsigned int
d_variety(int n)
{
	unsigned int enc = get_basic_int(2, 1);
	switch (enc) {
	case e_var_apply_token:
		consname("var_apply_token", n);
		    IGNORE d_token(n + 1);
		    IGNORE d_bitstream("var_apply_token", n + 1);
		    break;
	case e_var_cond:
		consname("var_cond", n);
		    IGNORE d_exp(n + 1);
		    IGNORE d_bitstream("var_cond", n + 1);
		    IGNORE d_bitstream("var_cond", n + 1);
		    break;
	case e_var_limits:
		consname("var_limits", n);
		    IGNORE d_signed_nat(n + 1);
		    IGNORE d_signed_nat(n + 1);
		    break;
	case e_var_width:
		consname("var_width", n);
		    IGNORE d_bool(n + 1);
		    IGNORE d_nat(n + 1);
		    break;
	default:
		fail("Bad variety value, 37", enc);
		break;
	}
	return(enc);
}


/* DECODE VERSION */

unsigned int
d_version(int n)
{
	unsigned int enc = get_basic_int(1, 1);
	switch (enc) {
	case e_make_version:
		consname("make_version", n);
		    IGNORE d_tdfint(n + 1);
		    IGNORE d_tdfint(n + 1);
		    break;
	case e_user_info:
		consname("user_info", n);
		    IGNORE d_string(n + 1);
		    break;
	default:
		fail("Bad version value, 38", enc);
		break;
	}
	return(enc);
}


/* DECODE SIMPLE VERSION LIST */

unsigned int
d_version_list(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_version(n + 1);
	}
	return(nl);
}


/* DECODE VERSION_PROPS */

unsigned int
d_version_props(int n)
{
	    consname("make_versions", n);
	    IGNORE d_version_list(n + 1);
	    return(0);
}
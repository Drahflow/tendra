/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
*/


/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header$
--------------------------------------------------------------------------*/

#ifndef dw2_config_key
#define dw2_config_key 1

#include "config.h"
#include "common_types.h"
#include "out.h"


#ifdef NEEDS_DEBUG_ALIGN

#define DWARF_MOD_VERSION	( DWARF_VERSION * 101 )
#define DW_CIE_MOD_VERSION	( DW_CIE_VERSION * 101 )

#else

#define DWARF_MOD_VERSION	DWARF_VERSION
#define DW_CIE_MOD_VERSION	DW_CIE_VERSION

#endif


extern long instr_count;
extern long fde_count;

#define count_ins(n)		if (instr_count >= 0) instr_count += n; \
				if (fde_count >= 0) fde_count += n
#define lost_count_ins()	instr_count = fde_count = -1
#define any_output		instr_count
#define reset_any_output	instr_count = 0


#define d_outnl() outnl()

extern void out8 PROTO_S ((void));
extern void out16 PROTO_S ((void));
extern void out32 PROTO_S ((void));
extern void dot_align PROTO_S ((long n));

extern void out_string PROTO_S ((char * s));
extern void start_string PROTO_S ((char * s));
extern void end_string PROTO_S ((void));
extern void enter_section PROTO_S ((char * s));
extern void exit_section PROTO_S ((void));
extern void outnl_comment PROTO_S ((char * s));
extern void outnl_comment_i PROTO_S ((char * s, long i));
extern void out_dwf_label PROTO_S ((long l, int set));
extern void out_code_label PROTO_S ((long l));
extern void out_dwf_dist_to_label PROTO_S ((long l));
extern void out_dwf_labdiff PROTO_S ((long lo, long hi));
extern void out_ext_label PROTO_S ((char * s));
extern void out_producer PROTO_S ((char * s));

extern int dw_is_const PROTO_S ((exp e));
extern exp dw_has_location PROTO_S ((exp e));
extern void dw2_locate_exp PROTO_S ((exp e, int locate_const, int cx));
extern void dw2_prepare_locate PROTO_S ((exp id));
extern void dw_at_procdetails PROTO_S ((void));
extern void dw2_locate_result PROTO_S ((shape sha));
extern void dw2_locate_val PROTO_S ((dg_where v));
extern void dw2_offset_exp PROTO_S ((exp e));
extern void dw2_cie PROTO_S ((void));

extern void dw2_data_aranges PROTO_S ((void));
extern void trace_dw_branch_exits PROTO_S ((exp e));

extern int dw_loc_equivalence PROTO_S ((exp a, exp b));
extern void dw_allocated PROTO_S ((dg_name nm, exp id));
extern void dw_deallocated PROTO_S ((dg_name nm));
extern void dw_all_deallocated PROTO_S ((void));


extern long dwarf_lab_num;

#define min_instr_size 4
#define framecode_factor 4
#define framedata_factor 4
#define next_dwarf_label() (++dwarf_lab_num)

#define dw_line_base -2	/* small negative for short loop end-conditions */
#define dw_line_range 16


extern void note_data PROTO_S ((int ll, bool ro));


#endif

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


/* 80x86/instr386decs.h */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:51 $
$Revision: 1.1.1.1 $
$Log: instr386.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
 * Revision 1.17  1997/10/10  18:25:22  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.16  1996/11/08  16:19:19  pwe
 * check_stack to check before modifying stack
 *
 * Revision 1.15  1996/07/31  12:57:19  pwe
 * restore alloca stack after longjump
 *
 * Revision 1.14  1996/05/20  14:30:33  pwe
 * improved 64-bit handling
 *
 * Revision 1.13  1996/05/13  12:51:59  pwe
 * undo premature commit
 *
 * Revision 1.11  1996/01/10  14:00:01  pwe
 * apply with varcallees within postlude
 *
 * Revision 1.10  1995/09/26  16:47:00  pwe
 * compare with zero to ignore previous overflow
 *
 * Revision 1.9  1995/09/13  14:25:17  pwe
 * tidy for gcc
 *
 * Revision 1.8  1995/09/08  12:51:22  pwe
 * exceptions improved
 *
 * Revision 1.7  1995/09/05  16:25:03  pwe
 * specials and exception changes
 *
 * Revision 1.6  1995/08/30  16:06:45  pwe
 * prepare exception trapping
 *
 * Revision 1.5  1995/08/23  09:42:53  pwe
 * track fpu control word for trap etc
 *
 * Revision 1.4  1995/08/14  13:53:51  pwe
 * several corrections, tail calls and error jumps
 *
 * Revision 1.3  1995/08/04  08:29:35  pwe
 * 4.0 general procs implemented
 *
 * Revision 1.2  1995/01/30  12:56:25  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:34:48  jmf
 * Initial revision
 *
**********************************************************************/


/**********************************************************************
                        instr386decs.h

   declares the higher level routines which output 80x86 instructions.

**********************************************************************/

#ifndef i386_key
#define i386_key 1


extern void add(shape sha, where a1, where a2, where dest);
extern void absop(shape sha, where a1, where dest);
extern void maxop(shape sha, where a1, where a2, where dest);
extern void minop(shape sha, where a1, where a2, where dest);
extern void sub(shape sha, where min, where from, where dest);
extern void mult(shape sha, where a1, where a2, where dest);
extern void multiply(shape sha, where a1, where a2, where dest);
extern void div0(shape sha, where bottom, where top, where dest);
extern void div1(shape sha, where bottom, where top, where dest);
extern void div2(shape sha, where bottom, where top, where dest);
extern int cmp(shape sha, where from, where min, int nt, exp e);
extern void negate(shape sha, where a, where dest);
extern void move(shape sha, where from, where to);
extern void mova(where from, where to);
extern void and(shape sha, where a1, where a2, where dest);
extern void or(shape sha, where a1, where a2, where dest);
extern void xor(shape sha, where a1, where a2, where dest);
extern void not(shape sha, where a, where dest);
extern void change_var(shape sha, where from, where to);
extern void change_var_check(shape sha, where from, where to);
extern void change_var_sh(shape sha, shape fsh, where from, where to);
extern void floater(shape sha, where from, where to);
extern void frnd0(shape sha, where from, where to);
extern void frnd1(shape sha, where from, where to);
extern void frnd2(shape sha, where from, where to);
extern void frnd3(shape sha, where from, where to);
extern void frnd4(shape sha, where from, where to);
extern void changefl(shape sha, where from, where to);
extern void shiftl(shape sha, where wshift, where from, where to);
extern void shiftr(shape sha, where wshift, where from, where to);
extern void rotatel(shape sha, where wshift, where from, where to);
extern void rotater(shape sha, where wshift, where from, where to);
extern void mod(shape sha, where bottom, where top, where dest);
extern void rem2(shape sha, where bottom, where top, where dest);
extern void rem0(shape sha, where bottom, where top, where dest);
extern void long_jump(exp e);
extern void initzeros(void);
extern where zero;
extern where fzero;
extern where dzero;
extern exp zeroe;
extern where ind_reg0;
extern where ind_reg1;
extern where ind_sp;
extern where sp;
extern where bp;
extern where reg0;
extern where reg1;
extern where reg2;
extern where reg3;
extern where reg4;
extern where reg5;
extern where reg_wheres[7];
extern where pushdest;
extern where cond1;
extern where cond2a;
extern where cond2b;
extern int cond1_set;
extern int cond2_set;
extern void decstack(int longs);
extern void callins(int longs, exp ind, int ret_stack_dec);
extern void jumpins(exp ind);
extern void retins(void);
extern int inmem(where w);
extern void fl_binop(unsigned char op, shape sha, where arg1, where arg2,
		     where dest, exp last_arg);
extern void fl_multop(unsigned char op, shape sha, exp arglist, where dest);
extern void fl_neg(shape sha, where from, where to);
extern void fl_abs(shape sha, where from, where to);
extern void test(shape sha, where a, where b);
extern void fl_comp(shape sha, where pos, where neg, exp e);
extern where flstack;
extern int in_fl_reg(exp e);
extern int in_fstack(exp e);
extern void movecont(where from, where to, where length, int nooverlap);
extern void load_stack0(void);
extern int in_reg(exp e);
extern void end_contop(void);
extern int top_regsinuse;
extern int lsmask[33];
extern int first_fl_reg;
extern int fstack_pos;
extern exp overflow_e;
extern void stack_return(int longs);
extern int bad_from_reg(where f);

extern void bits_to_mem(exp e, exp d, ash stack);
extern void mem_to_bits(exp e, shape sha, where dest, ash stack);

extern void setup_fl_ovfl(exp e);
extern void test_fl_ovfl(exp e, where dest);
extern void reset_fpucon(void);
extern exp find_stlim_var(void);
extern void checkalloc_stack(where sz, int b);	/* uses reg1 */
extern void special_ins(char *id, exp args, where dest);

extern exp ferrmem;
extern int ferrsize;
extern int fpucon;
extern int cmp_64hilab;

extern void save_stack(void);
extern void restore_stack(void);

extern void start_asm(void);
extern void end_asm(void);
extern void asm_ins(exp e);


#endif

/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* ANSI PROMOTION RULES */

#ifndef __TCC_PROMOTION_H
#define __TCC_PROMOTION_H

#pragma token VARIETY __prom_ushort # ~int_promot
#pragma token PROC ( VARIETY ) VARIETY __prom # ~promote
#pragma promote char:int
#pragma promote unsigned char:int
#pragma promote signed char:int
#pragma promote short:int
#pragma promote int:int
#pragma promote unsigned int:unsigned int
#pragma promote long:long
#pragma promote unsigned long:unsigned long

#pragma TenDRA begin
#pragma TenDRA no external declaration allow
#pragma TenDRA longlong type allow
#pragma promote long long:long long
#pragma promote unsigned long long:unsigned long long
#pragma TenDRA end
#pragma TenDRA begin

#ifdef __ushort_to_int
#pragma promote unsigned short:int
#else
#pragma promote unsigned short:__prom_ushort
#endif
#pragma promote __prom_ushort:__prom_ushort
#pragma compute promote __prom

#pragma no_def __prom_ushort __prom
#undef __prom_ushort
#undef __prom
#undef __ushort_to_int

#endif

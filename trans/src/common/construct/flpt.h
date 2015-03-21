/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef flpt_key
#define flpt_key 1

#include <limits.h>

#include <tdf/nat.h>

#include <construct/installtypes.h>
#include <construct/flpt.h>

#include <main/flags.h>

#include <local/fbase.h>


#if FBASE == 10

/* FBASE 10 is obsolete */

#define MANT_SIZE 40
#define MANT_SIZE_MAX 40

#define Fdig unsigned char

#define FNUM_SIZE 65		/* max size required by flt2str */
/* MANT_SIZE + 1(sign) + 1(point) + 2(E+sign) + log(MAX_LONG) + 1(NULL) */

#define E_MIN	(-1000000)	/* (LONG_MIN/10) doesnt work on 80386 cc
				*/
#define E_MAX	(LONG_MAX / 10)

/* Function status values:   */
#define OKAY		0
#define EXP2BIG	(-1)
#define SYNTAX		(-2)
#define DIVBY0		(-3)

/* Rounding types:   */
#define R2ZERO	0
#define R2PINF	1
#define R2NINF	2
#define R2NEAR	3

/* floating point representation */
typedef struct _flt {
  Fdig mant[MANT_SIZE]; /* mantissa digit values [0-9] (NOT '0' to '9') */
  /* point is between 1st and 2nd digits */
  int sign;		/* -1: negative; +1: positive; 0: value is zero */
  int exp;		/* signed exponent; in range E_MIN..E_MAX */
} flt;

#else

/* all installers should use this definition */

/* MANT_SIZE is the number of mantissa array elements */
#ifndef MANT_SIZE
#define MANT_SIZE 8
#endif

/* MANT_SIZE_MAX is the number of mantissas array elements that
 * supported by the platform's largest floating point type (double or
 * long double)
 */
#ifndef MANT_SIZE_MAX
#define MANT_SIZE_MAX 8
#endif

#define Fdig unsigned short
/* FBITS is the number of bits in one array element */
#define FBITS 16

#define E_MIN	(-16384)
#define E_MAX	(LONG_MAX / FBASE)

/* Function status values:   */
#define OKAY		0
#define EXP2BIG	(-1)
#define SYNTAX		(-2)
#define DIVBY0		(-3)

/* Rounding types:   */
#define R2ZERO	3
#define R2PINF	2
#define R2NINF	1
#define R2NEAR	0

typedef struct _flt {
  Fdig mant[10];
  /* point is between 1st and 2nd digits */
  int sign;		/* -1: negative; +1: positive; 0: value is zero */
  int exp;		/* signed exponent; in range E_MIN..E_MAX */
} flt;	/* floating point representation */


/* type for result of conversion of reals to ints */
typedef struct r2l_t {
	int i1; /* least significant */
	int i2;
	int i3;
	int i4;	/* most significant */
} r2l;

#endif

typedef struct flt64_t {
  int big;		/* more significant 32 bits */
  unsigned int small;	/* less significant 32 bits */
} flt64;
/* used to convert flpt number which are integers into a 64 bit
 * representation */


extern void init_flpt(void);
extern flpt new_flpt(void);
extern void flpt_ret(flpt f);
extern int cmpflpt(flpt a, flpt b, int testno);
extern flpt floatrep(int n);
extern flpt floatrep_unsigned(unsigned int n);
extern flt *flptnos;

/* floatingpoint functions - are these needed externally??? */
extern void flt_zero(flt *f);
extern void flt_copy(flt f, flt *res);
extern int  flt_add(flt f1, flt f2, flt *res);
extern int  flt_sub(flt f1, flt f2, flt *res);
extern int  flt_mul(flt f1, flt f2, flt *res);
extern int  flt_div(flt f1, flt f2, flt *res);
extern int  flt_cmp(flt f1, flt f2);
extern void flt_round(flt f, flt *res);
extern void flpt_newdig(unsigned int dig, flt *res, int base);
extern void flpt_scale(int decexp, flt *res, int base);
extern void flpt_round(int rdnmd, int pos, flt *res);
extern int flpt_bits(floating_variety fv);
extern int flpt_round_to_integer(int rndmd, flt *f);

#if FBASE != 10
extern r2l real2longs_IEEE(flt *f, int sw);
#endif

extern int fzero_no;
extern int fone_no;


extern flt64 flt_to_f64(flpt fp, int sg, int *ov);
extern flpt f64_to_flt(flt64 a, int sg);
extern int f64_to_flpt(flt64 a, int sg, int *pr, int sz);
extern flt64 int_to_f64(int i, int sg);
extern flt64 exp_to_f64(exp e);


#endif

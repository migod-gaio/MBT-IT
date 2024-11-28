/* example interrupt control */
/*
#define WinAMS_SPMC_DI	_WinAMS_SPMC_DI()
inline void _WinAMS_SPMC_DI()
{
	__asm("	di\n");
}

#define WinAMS_SPMC_EI	_WinAMS_SPMC_EI()
inline void _WinAMS_SPMC_EI()
{
	__asm("	ei\n");
}
*/

/* inport interrupt control */
#define WINAMS_SPMC_U4_INT


/* The maximum nuber of the condition to measure coverage */
#define WINAMS_SPMC_MCDC_MAXCONDCNT	127	/* 255 or 511 can expand it */

/* The number if the greatest nests measuring coverage */
#define WINAMS_SPMC_MCDC_MAXCONDNEST	32	/* 64 or 128 can expand it */

#if defined(__S12Z__) || defined(__HCS12__)	/* v6.0.3 */
#define THREE_BYTE_POINTER_USE 1
#else	/* defined(__S12__) */
#define THREE_BYTE_POINTER_USE 0
#endif /* defined(__S12__) */

/* A user defines the type of the string of the file name */
#define WinAMS_SPMC_BASE_TFILENAME char			/* base type=char */
/* #define WinAMS_SPMC_BASE_TFILENAME signed char */	/* base type=signed char */
/* #define WinAMS_SPMC_BASE_TFILENAME unsigned char */	/* base type=unsigned char */
#define WinAMS_SPMC_TABLE_PTR_TATTR1			/* type tatt1 *name */
#define WinAMS_SPMC_TABLE_PTR_TATTR2			/* type *tatt2 name */
/* #define WinAMS_SPMC_TABLE_PTR_TATTR1 far */		/* example */
#define WinAMS_SPMC_TABLE_TATTR				/* type tatt name[] */
/* #define WinAMS_SPMC_TABLE_TATTR far */		/* example */
#if THREE_BYTE_POINTER_USE	/* v6.0.3 */
#define WinAMS_SPMC_CVT_TABLE_PTR(fname)	((unsigned long)(fname))		/* table pointer convert */
#else	/* THREE_BYTE_POINTER_USE */
#define WinAMS_SPMC_CVT_TABLE_PTR(fname)	(fname)		/* table pointer convert */
#endif 	/* THREE_BYTE_POINTER_USE */
/* #define WinAMS_SPMC_CVT_TABLE_PTR(fname)	((WinAMS_SPMC_TFILENAME_PTR)((unsigned long)(fname) | 0xff0000)) */		/* example */
#define WinAMS_SPMC_CONST const /* const table */
/* #define WinAMS_SPMC_CONST */ /* not const table */
#ifndef WinAMS_SPMC_Init_arg_void
#define WinAMS_SPMC_Init_arg_void 0 /* 0: WinAMS_SPMC_Init()   1: WinAMS_SPMC_Init(void) v6.3 */
#endif

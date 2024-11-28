/* WinAMS_SPMC_Com.c(v6.3) */
#include "winAMS_Spmc_Com.h"

#define BOOL WinAMS_SPMC_BOOL

typedef WinAMS_SPMC_U4 U4;
typedef WinAMS_SPMC_U1 U1;
typedef WinAMS_SPMC_U2 U2;

volatile U1	WinAMS_SPMC;
volatile U4	WinAMS_SPMC_bits[WINAMS_SPMC_MCDC_MAXCONDNEST][(WINAMS_SPMC_MCDC_MAXCONDCNT+1)/16];
volatile U2	WinAMS_SPMC_expcnt_Ary[WINAMS_SPMC_MCDC_MAXCONDNEST];
volatile U2	WinAMS_SPMC_nest;
volatile U2	WinAMS_SPMC_expcnt;
volatile U4	WinAMS_SPMC_index;
volatile U1	WinAMS_SPMC_Blk_ID_Com;
volatile U1	WinAMS_SPMC_Line_Com;

#if THREE_BYTE_POINTER_USE	/* v6.0.3 */
unsigned long WinAMS_SPMC_filename;
#else /* THREE_BYTE_POINTER_USE */

#if __COMPILER_FCC907__
volatile WinAMS_SPMC_CONST WinAMS_SPMC_BASE_TFILENAME WinAMS_SPMC_TABLE_PTR_TATTR1*WinAMS_SPMC_TABLE_PTR_TATTR2	WinAMS_SPMC_filename;
#else
WinAMS_SPMC_CONST WinAMS_SPMC_BASE_TFILENAME WinAMS_SPMC_TABLE_PTR_TATTR1*WinAMS_SPMC_TABLE_PTR_TATTR2	volatile WinAMS_SPMC_filename;
#endif /* __COMPILER_FCC907__ */

#endif /* THREE_BYTE_POINTER_USE */

volatile BOOL	WinAMS_SPMC_resVal;

volatile U2	WinAMS_SPMC_maxCondCnt;
volatile U2	WinAMS_SPMC_maxCondNest;
volatile U1	WinAMS_SPMC_Lock;
/* v6.3 */
#if WinAMS_SPMC_Init_arg_void
void (*volatile WinAMS_SPMC_Init_ptr)(void) = WinAMS_SPMC_Init;
#else
void (*volatile WinAMS_SPMC_Init_ptr)() = WinAMS_SPMC_Init;
#endif


/* v6.3 */
#if WinAMS_SPMC_Init_arg_void
void WinAMS_SPMC_Init(void)
#else
void WinAMS_SPMC_Init()
#endif
{
	WinAMS_SPMC_maxCondCnt = WINAMS_SPMC_MCDC_MAXCONDCNT;
	WinAMS_SPMC_maxCondNest = WINAMS_SPMC_MCDC_MAXCONDNEST;
	WinAMS_SPMC_Lock = 0;
	WinAMS_SPMC_nest = 0;
	WinAMS_SPMC_resVal = 0;
	WinAMS_SPMC_Blk_ID_Com = 0;
	WinAMS_SPMC_Line_Com = 0;
}

BOOL WinAMS_SPMC_Exp(U2 expID,BOOL exp)
{
#if defined(WinAMS_SPMC_DI) && defined(WinAMS_SPMC_EI)
	WinAMS_SPMC_DI();
#endif
	if (WinAMS_SPMC_Lock == 0) {
		U2 nest;
		WinAMS_SPMC_Lock = 1;
		nest = WinAMS_SPMC_nest-1;
		if (expID < WINAMS_SPMC_MCDC_MAXCONDCNT &&
		    nest < WINAMS_SPMC_MCDC_MAXCONDNEST) {
			U1 amsbit = exp ? 0x3 : 0x2;
			WinAMS_SPMC_bits[nest][expID>>4] |= (U4)amsbit << ((expID & 0xf) << 1);
		}
		WinAMS_SPMC_Lock = 0;
	}
#if defined(WinAMS_SPMC_DI) && defined(WinAMS_SPMC_EI)
	WinAMS_SPMC_EI();
#endif
	return exp;
}

BOOL WinAMS_SPMC_Clr(U2 expcnt)
{
#if defined(WinAMS_SPMC_DI) && defined(WinAMS_SPMC_EI)
	WinAMS_SPMC_DI();
#endif
	if (WinAMS_SPMC_Lock == 0) {
		U2 nest;
		WinAMS_SPMC_Lock = 1;
		nest = WinAMS_SPMC_nest++;
		if (nest < WINAMS_SPMC_MCDC_MAXCONDNEST) {
			U2 i,n;
			n = (expcnt < WINAMS_SPMC_MCDC_MAXCONDCNT) ? expcnt : WINAMS_SPMC_MCDC_MAXCONDCNT;
			n = (n >> 4) + 1;
			for (i = 0 ; i < n ; i++)
				WinAMS_SPMC_bits[nest][i] = 0;
			WinAMS_SPMC_expcnt_Ary[nest] = expcnt; 
		}
		WinAMS_SPMC_Lock = 0;
	}
#if defined(WinAMS_SPMC_DI) && defined(WinAMS_SPMC_EI)
	WinAMS_SPMC_EI();
#endif
	return 0;
}

BOOL WinAMS_SPMC_Res_Com(WinAMS_SPMC_TFILENAME_PTR file,U4 index,BOOL res)
{
#if defined(WinAMS_SPMC_DI) && defined(WinAMS_SPMC_EI)
	WinAMS_SPMC_DI();
#endif
	if (WinAMS_SPMC_Lock == 0) {
		U2 nest;
		U2 expcnt;
		WinAMS_SPMC_Lock = 1;
		nest = --WinAMS_SPMC_nest;
		if (nest < WINAMS_SPMC_MCDC_MAXCONDNEST) {
			expcnt = WinAMS_SPMC_expcnt_Ary[nest];
			if (expcnt < WINAMS_SPMC_MCDC_MAXCONDCNT+1) {
				U1 amsbit = res ? 0x3 : 0x2;
				WinAMS_SPMC_bits[nest][expcnt>>4] |= (U4)amsbit << ((expcnt & 0xf) << 1);
			}
		}
		else {
			expcnt = WINAMS_SPMC_MCDC_MAXCONDCNT+1;
			if (nest == 0xffff) {
				WinAMS_SPMC_nest = 0; 
			}
		}
#ifdef WinAMS_SPMC_CVT_TABLE_PTR							/* v3.5 */
		WinAMS_SPMC_filename = WinAMS_SPMC_CVT_TABLE_PTR(file);	/* v3.5 */
#else
		WinAMS_SPMC_filename = file;
#endif
		WinAMS_SPMC_expcnt = expcnt;
		WinAMS_SPMC_index = index;
		WinAMS_SPMC = 2;
		WinAMS_SPMC_Lock = 0;
	}
#if defined(WinAMS_SPMC_DI) && defined(WinAMS_SPMC_EI)
	WinAMS_SPMC_EI();
#endif
	return res;
}

BOOL WinAMS_SPMC_Com(WinAMS_SPMC_TFILENAME_PTR file,U4 index)
{
#if defined(WinAMS_SPMC_DI) && defined(WinAMS_SPMC_EI)
	WinAMS_SPMC_DI();
#endif
	if (WinAMS_SPMC_Lock == 0) {
		WinAMS_SPMC_Lock = 1;
#ifdef WinAMS_SPMC_CVT_TABLE_PTR							/* v3.5 */
		WinAMS_SPMC_filename = WinAMS_SPMC_CVT_TABLE_PTR(file);	/* v3.5 */
#else
		WinAMS_SPMC_filename = file;
#endif
		WinAMS_SPMC_index = index;
		WinAMS_SPMC = 1;
		WinAMS_SPMC_Lock = 0;
	}
#if defined(WinAMS_SPMC_DI) && defined(WinAMS_SPMC_EI)
	WinAMS_SPMC_EI();
#endif
	return 0;
}


BOOL WinAMS_SPMC_C1_Clr_Com(WinAMS_SPMC_TFILENAME_PTR file,U4 index,U2 expcnt)
{
#if defined(WinAMS_SPMC_DI) && defined(WinAMS_SPMC_EI)
	WinAMS_SPMC_DI();
#endif
	if (WinAMS_SPMC_Lock == 0) {
		U2 nest;
		WinAMS_SPMC_Lock = 1;
		nest = WinAMS_SPMC_nest++;
		if (nest < WINAMS_SPMC_MCDC_MAXCONDNEST) {
			U2 i,n;
			n = (expcnt < WINAMS_SPMC_MCDC_MAXCONDCNT) ? expcnt : WINAMS_SPMC_MCDC_MAXCONDCNT;
			n = (n >> 4) + 1;
			for (i = 0 ; i < n ; i++)
				WinAMS_SPMC_bits[nest][i] = 0;
			WinAMS_SPMC_expcnt_Ary[nest] = expcnt; 
		}
#ifdef WinAMS_SPMC_CVT_TABLE_PTR							/* v3.5 */
		WinAMS_SPMC_filename = WinAMS_SPMC_CVT_TABLE_PTR(file);	/* v3.5 */
#else
		WinAMS_SPMC_filename = file;
#endif
		WinAMS_SPMC_index = index;
		WinAMS_SPMC = 1;
		WinAMS_SPMC_Lock = 0;
	}
#if defined(WinAMS_SPMC_DI) && defined(WinAMS_SPMC_EI)
	WinAMS_SPMC_EI();
#endif
	return 0;
}


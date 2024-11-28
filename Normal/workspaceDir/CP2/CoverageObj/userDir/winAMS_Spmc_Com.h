/* WinAMS_SPMC_Com.h(v6.3) */
#include "winAMS_SpmcDefine_Com.h"

#define WinAMS_SPMC_BOOL int

#ifdef WINAMS_SPMC_U4_INT	/* v6.3 */
typedef unsigned int  WinAMS_SPMC_U4;
#else
typedef unsigned long WinAMS_SPMC_U4;
#endif
typedef unsigned char WinAMS_SPMC_U1;
typedef unsigned short WinAMS_SPMC_U2;

/* v3.6 */
typedef WinAMS_SPMC_CONST WinAMS_SPMC_BASE_TFILENAME WinAMS_SPMC_TABLE_PTR_TATTR1*WinAMS_SPMC_TABLE_PTR_TATTR2 WinAMS_SPMC_TFILENAME_PTR;

#ifdef __cplusplus
#define WinAMS_SPMC_bool bool
extern "C" {
#endif  /* __cplusplus */

WinAMS_SPMC_BOOL WinAMS_SPMC_Exp(WinAMS_SPMC_U2 expID,WinAMS_SPMC_BOOL exp);
WinAMS_SPMC_BOOL WinAMS_SPMC_Clr(WinAMS_SPMC_U2 expcnt);

/* v3.6 */
WinAMS_SPMC_BOOL WinAMS_SPMC_Res_Com(WinAMS_SPMC_TFILENAME_PTR file,WinAMS_SPMC_U4 index,WinAMS_SPMC_BOOL res);

WinAMS_SPMC_BOOL WinAMS_SPMC_Com(WinAMS_SPMC_TFILENAME_PTR file,WinAMS_SPMC_U4 index);
/* v6.3 */
#if WinAMS_SPMC_Init_arg_void
void WinAMS_SPMC_Init(void);
#else
void WinAMS_SPMC_Init();
#endif
WinAMS_SPMC_BOOL WinAMS_SPMC_C1_Clr_Com(WinAMS_SPMC_TFILENAME_PTR file,WinAMS_SPMC_U4 index,WinAMS_SPMC_U2 expcnt);
#ifdef __cplusplus
}

WinAMS_SPMC_bool WinAMS_SPMC_Exp_PP(WinAMS_SPMC_U2 expID,WinAMS_SPMC_bool exp);
WinAMS_SPMC_bool WinAMS_SPMC_Clr_PP(WinAMS_SPMC_U2 expcnt);

/* v3.6 */
WinAMS_SPMC_bool WinAMS_SPMC_Res_PP_Com(WinAMS_SPMC_TFILENAME_PTR file,WinAMS_SPMC_U4 index,WinAMS_SPMC_bool res);

WinAMS_SPMC_bool WinAMS_SPMC_PP_Com(WinAMS_SPMC_TFILENAME_PTR file,WinAMS_SPMC_U4 index);

WinAMS_SPMC_bool WinAMS_SPMC_C1_Clr_PP_Com(WinAMS_SPMC_TFILENAME_PTR file,WinAMS_SPMC_U4 index,WinAMS_SPMC_U2 expcnt);
#endif  /* __cplusplus */

/* v3.2 */
extern volatile WinAMS_SPMC_BOOL	WinAMS_SPMC_resVal;

extern volatile WinAMS_SPMC_U1	WinAMS_SPMC;

/* v3.6 */
extern volatile WinAMS_SPMC_U1	WinAMS_SPMC_Blk_ID_Com;
extern volatile WinAMS_SPMC_U1	WinAMS_SPMC_Line_Com;

#include "winAMS_Spmc_Com.h"
static WinAMS_SPMC_CONST WinAMS_SPMC_BASE_TFILENAME WinAMS_SPMC_TABLE_TATTR WinAMS_SPMC_info_file[] = "20241128235857;src_c\\src.cvInfo";

#line 1 "C:\\Users\\TestEnv\\Desktop\\migo\\R10\\IT\\MBT-RD11\\MBT-IT\\userDir\\src.c"
double In1, Out1, Gain=10;
#line 3
void Subsystem ()
{
 WinAMS_SPMC_Com(WinAMS_SPMC_info_file,1),Out1 = In1 * Gain;
}
#line 8
void main(){
#line 10
 WinAMS_SPMC_Com(WinAMS_SPMC_info_file,2);}

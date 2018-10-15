// *****************************************************************************
// Extracto de PWRC_v9e 
// CESE 2018 - R.Oliva - Testing de software TP3
// 14.10.2018
//
// ESTADISTICAS ESPECIALES
//
// typedef struct sp_stats_holder {
//     // Wdir components..
//     FP DSampleDeg;   // - WDIR Sample received from RS485, 0.0-360.0 degs
//     FP DSampleRad;   // WDIR sample conv. To rads..
//     FP Vvx;          // = Instant Unit Vector x component
//     FP Vvy;          // = Instant Unit Vector y component
//     FP A_v_vx;       // = Average of Vx
//     FP A_v_vy;       // = Average of Vy
//     FP WD_Av;        // = WDIR average – corrected- in Deg
//     // RHO and Normalize components..
//     FP A_v_Rho;
//     FP CSampleRho;
//     // Vbint components.. (not used 9-.4.2012
//     // Vbmeteo components.. (Not used..)
//  } StHSp;
//
//  RAM HOLDER:
//    StHSp AUX;
//
// *****************************************************************************

#include "stats_CL2_5sp.h"


// *****************************************************************************
// 7) Direccion de Viento
// *****************************************************************************
// FP AUX.DSampleRad contains WDIR from 0.0 to 360.0, read from RS485
// - METEO in UART1 (9.4.2012)

void SpStats_WD(uint16_t *cnt) {
#define K_PIOVER180 0.01745329

FP ftemp;    // Temporal floating point variable..
uint16_t j_av;  // Temp counter, change to uint16_t
   j_av = *cnt;
   // Convert to Rads..
   AUX.DSampleRad = K_PIOVER180 * AUX.DSampleDeg;
   // Find sin, cos of converted angle
   AUX.Vvx = sin(AUX.DSampleRad);
   AUX.Vvy = cos(AUX.DSampleRad);
   // Average these two vector components..
   // Comp. in x:
      ftemp = AUX.A_v_vx*(FP)(j_av - 1)+ AUX.Vvx ;
      ftemp = ftemp /(FP)( j_av);
        /* No FP integrity checking in this compiler.. */
      AUX.A_v_vx = ftemp;   // AUX.A_v_vx  contains x average..
   // Comp. in y:
      ftemp = AUX.A_v_vy*(FP)(j_av - 1)+ AUX.Vvy ;
      ftemp = ftemp /(FP)( j_av);
        /* No FP integrity checking in this compiler.. */
      AUX.A_v_vy = ftemp;   // AUX.A_v_vy  contains y average..
    // Could require range checking..
    // End Avg_calc ********************************************
}

// *****************************************************************************
// 8) Rho Stats   ( Especial - Densidad Aire)
//     Only calculate RHO Average..
//     FP A_v_Rho;
//     FP CSampleRho;
// *****************************************************************************

void SpStats_Rho( uint16_t *cnt) {
FP ftemp;    // Temporal floating point variable..
uint16_t j_av;  // Temp counter
   j_av = *cnt;
   /*First average in float */
      ftemp = AUX.A_v_Rho*(FP)(j_av - 1)+ AUX.CSampleRho;
      ftemp = ftemp /(FP)( j_av);
        /* No FP integrity checking in this compiler.. */
      AUX.A_v_Rho = ftemp;   /* Pa.A_v es el “Pa.Aj” ahora.. */
      // Could require range checking..
// End Avg_calc ********************************************
// No other calculations necessary for RHO..
}

// **************************************************************************************
// 7. Wind direction - unit vector avg
// **************************************************************************************
void SpStats_WD_Init(void){                // Special - Wind direction - unit vector avg
         AUX.A_v_vx = 0.0;
         AUX.A_v_vy = 0.0;                                     
}

// **************************************************************************************
// 8. Rho: Air densiti calc init.
// **************************************************************************************
void SpStats_Rho_Init(void){               // Sp. Air density
         AUX.A_v_Rho = AUX.CSampleRho;
}


// **********************************************************************************
// void Stats_Call_Init()
// After Powr UP or Reset, these _Init() routines are called, no RAM values are saved
// except the current REG_Counter, obviously the filename and status of measurement. 
// Upon PwrUp or Reset, the system recovers REG_Counter, status and filename and 
// continues the measurement reseting all stats with _Init() calls. After the period 
// (1 minute normally), the Stats values will be saved to the current file at position 
// REG_Counter+1. Also an event will be registered in current EV file.
// 4.2012 VB_Aux not used
// Addition on v5N WTG Current 31.7.2014
// **********************************************************************************
void Stats_Call_Init(void) {
	j_aver = 2;

   #ifdef FULL_STATS_CALC    
 	Stats_Pae_Init();             // WTG Power
	Stats_VB_Init();              // Main Battery
	Stats_VV_Init();              // Wind speed
	Stats_T_Init();		          // Temperature
	Stats_Pa_Init();              // Atm. Pressure
    Stats_Iae_Init();             // WTG Current 31.7.2014
   #endif    
	SpStats_WD_Init();		      // Wdir.
	SpStats_Rho_Init();           // Sp. Air density
	// SpStats_AuxB_Init();       // Sp. Aux battery
	// TSTAT.VV_NORM0 = 0.0;      // Norm. WSpeed 7.11.06
}


// *****************************************************************************
// COMPUTO DE PROMEDIO DIRECCION / UNIT VECTOR AVG.5.11.2006
// Add Function for Calculating WDIR average..
// Add 17-6-2012 FlagPrintMeteo flag to avoid Modbus disturbance..
// *****************************************************************************
 
void Stats_Find_WDIR_Av(void){
    // 10c.4)    DIR
    // Upon Save time (1/min)..:
    // AUX.WD_Av = K_180overPi * atan2(AUX.A_v_vx, AUX.A_v_vy);
    // If(AUX.WD_Av < 0.0) AUX.WD_Av = AUX.WD_Av + 360.0;
    // USE (AUX.WD_Av)
    // a)	To find ELEG value
    // b)	To save on SD.. 
    AUX.WD_Av = K_180_OVER_PI * atan2(AUX.A_v_vx, AUX.A_v_vy);
    if(AUX.WD_Av < 0.0) {
         AUX.WD_Av = AUX.WD_Av + 360.0;
         }
    if(Flag_Print_METEO){
       printf("\n\r Avg_WDIR:, %3.1f ", AUX.WD_Av);
       }
}

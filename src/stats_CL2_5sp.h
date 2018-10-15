// *****************************************************************************
// stats_CL2_5sp.h (for CEEDLING Tests) R.Oliva 10.2018
// extracted from statCL2-5VN.h / .c
// PWRC/ii v2 - rev.31.07.2014 - Add Iaer Stats..
// Agrupa Stats calculos para
// Sistemas PWRC, En este caso:
// PWRC/ii en Placas CL2bm1
// *****************************************************************************
// PWRC/12  Rev. 20-.11.06 - Add Flag_Pr_Meteo
// 20.11.06 v11_Add BINs.. 21.11.06 Update..
// 29.11.06 REFORMAT de BIN read - 29.11.06 Desde 20m/s para arriba bins de 1m/s (ver.h)
// v2 Auxiliary function for protected increment of EE counter..
// v2 20.2.2007
// *****************************************************************************
// PWRC/ii - 10.04.2012 
// Placa CL2bm1 basadas en ATMega1284P / 14.76MHz
// - Eliminamos VBint components, no utilizados en sp_stats_holder
// - v4 On PWRC2 25.10.2012 Correct VVNORM calculation
// - v4-VN.c -> unsigned char Stats_Find_BIN(unsigned char eleg)
// (v8 of main) Modified for "Binning with VV_NORM" (in statsCL2-4VN.c,/.h)
// Function "unsigned char Stats_Find_BIN(unsigned char eleg)"
// 5.5.2014 - Add FindBIN with VV_NORM0 (normalized to 1.225kg/m3) instead
//            of former VV.A_v
// (5VN) v2 Add Iaer Stats, to be saved to SD.. 31.7.2014


#include <stdio.h>
#include <stdint.h>    
#include <math.h>

// *****************************************************************************
//         Templates
// *****************************************************************************

#define FP float

#ifdef FULL_STATS_CALC
typedef struct stats_holder {
     FP A_v;          // = Promedio acumulado (T.Aj-1) Float
     FP CSample;      // = Muestra actual escalada a Float (Current Simple = xj)
     FP ssq;          // = "Sigma Squared" acumulado anterior (sj-1) Float
     FP CSample_max;  // = Máximo registrado en la muestra actual (Float)
     FP CSample_min;  // = Mínimo registrado en la muestra actual (Float)
} StH;
#endif

// For these, we might define a specialized Stat_holder..
typedef struct sp_stats_holder {
     // Wdir components..
     FP DSampleDeg;   // - WDIR Sample received from RS485, 0.0-360.0 degs
     FP DSampleRad;   // WDIR sample conv. To rads..
     FP Vvx;          // = Instant Unit Vector x component
     FP Vvy;          // = Instant Unit Vector y component
     FP A_v_vx;       // = Average of Vx
     FP A_v_vy;       // = Average of Vy
     FP WD_Av;        // = WDIR average – corrected- in Deg
     // RHO and Normalize components..
     FP A_v_Rho;
     FP CSampleRho;
     // Vbint components (not used 2012..
     // Vbmeteo components.. (Not used..)
} StHSp;

// *****************************************************************************
//         Definitions..
// *****************************************************************************

// For RHO calcs, suppose (vOK 2012)
#define RCONST_DRY_AIR 287.05
#define CONST_UNITS 100.0
#define KELVIN_ADJ 273.15
#define RHO_DEF 1.225
#define RHO_ERR 1

// For WDIR
#define K_180_OVER_PI 57.295779


// *****************************************************************************
//         Variables
// *****************************************************************************

// unsigned int j_aver = 0; - redefine in test 10.2018
uint16_t j_aver;    // will be defined in _5sp.c
#ifdef FULL_STATS_CALC
StH Pa;        // Crea en RAM la estructura de stats Pa –(Presion Atm.)..
StH T;		   // Crea en RAM la estructura T (temperatura exterior) ..
StH VV;        // Crea en RAM la estructura VV (velocidad de viento) ..
StH Pae;       // Crea en RAM la estructura Pae (Potencia del Aerogenerador) ..
StH VB;        // Crea en RAM la estructura VB (Tensión de Batería ppal.) ..
// 31.7.2014 v5VN - Add Iaero
StH Iae;       // Crea en RAM la estructura Iae (Corriente del Aerogenerador) ..
#endif 

//  Special Structure
StHSp AUX;

extern unsigned char New_Sample_Flag;  //  10.4.2012 Defined in main and triggered by 
                                          // new value set in COM1. In normal CL2s, this
                                          // was triggerd by Timer1 -1sec..  
unsigned char Stat_Err_Flag;
//extern float  FV_IAero;       // Ch0 from AD..
//extern float  FV_Ch0;         // Ch0 is V_BAT, from M4/E3 ADC 03-2012
//extern float  FV_Ch1;         // Ch0 is IAero, from M4/E3 ADC 03-2012 
//extern float  FV_Ch7;         // Ch7 is Product of Vbat*IAero in ADPRocess() 03-2012
//extern float  FV_OTemp;       // OutDoor - Temp [ºC] from METEO/2
//extern float  FV_OBaro;       // OutDoor Temp  [mBar] from METEO/2
//extern float  FV_OWind;       // OutDoor WindSpeed [m/s] from METEO/2
//extern float  FV_OWDir;       // OutDoor WindDirection  [º] from METEO/2
//extern float  VV_NORM0;       // Normalized WSpeed..

//extern bit Flag_Print_METEO;  // Print on/off messages..Used also in v2 4-2012

//unsigned char WBin_DegCompl_tot;       // Degree 0-100 of completion TOTAL SET 21.11.06
//unsigned char WBin_DegCompl_IEC;       // Degree 0-100 of completion IEC SET

// *****************************************************************************
//         Function definitions
// *****************************************************************************

// Initialization routines:
void SpStats_WD_Init(void);            // Special - Wind direction - unit vector avg
void SpStats_Rho_Init(void);           // Sp. Air density
// void SpStats_AuxB_Init(void);        // Sp. Aux battery10.4.2012 not used
// All together..
void Stats_Call_Init(void);            // Calls a Sequence of the above.. 5.11.06 

// Add Function for copying FV values to sample holders..
// Returns 0 if new samples available, not zero if not..
unsigned char Stats_Read_Samples(void);

// Main Sp  stats routines:
void SpStats_WD(uint16_t *cnt);
void SpStats_Rho(uint16_t *cnt);
//void SpStats_AuxB( unsigned int *j_av);  10.4.12 not used


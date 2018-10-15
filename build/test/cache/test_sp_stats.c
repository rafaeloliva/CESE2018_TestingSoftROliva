#include "build/temp/_test_sp_stats.c"
#include "stats_CL2_5sp.h"
#include "unity.h"






void setUp(void) {

   Stats_Call_Init();

   AUX.DSampleDeg = 120.0;

   AUX.CSampleRho = 1.1;

}



void tearDown(void) {

}



void test_SpStats_WD(void) {



   SpStats_WD(&j_aver);



   UnityAssertFloatsWithin((UNITY_FLOAT)((0.1)), (UNITY_FLOAT)((0.43301)), (UNITY_FLOAT)((AUX.A_v_vx)), (

  ((void *)0)

  ), (UNITY_UINT)(19));

   UnityAssertFloatsWithin((UNITY_FLOAT)((0.1)), (UNITY_FLOAT)((-0.25)), (UNITY_FLOAT)((AUX.A_v_vy)), (

  ((void *)0)

  ), (UNITY_UINT)(20));

   Stats_Find_WDIR_Av();

   UnityAssertFloatsWithin((UNITY_FLOAT)((0.1)), (UNITY_FLOAT)((120.0)), (UNITY_FLOAT)((AUX.WD_Av)), (

  ((void *)0)

  ), (UNITY_UINT)(22));

}

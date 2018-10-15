#include "build/temp/_test_sp_stats.c"
#include "stats_CL2_5sp.h"
#include "unity.h"






float SampleDeg[] ={

    0.0,0.0,

    0.0,0.0,5.0,356.0,2.0,

    0.0,359.0,5.0,1.0,358.2 };







float SampleDeg2[] ={

    0.0,0.0,

    190.0,190.0,175.0,180.0,190.0,

    190.8,191.0,193.0,192.0,190.0};



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

  ), (UNITY_UINT)(32));

   UnityAssertFloatsWithin((UNITY_FLOAT)((0.1)), (UNITY_FLOAT)((-0.25)), (UNITY_FLOAT)((AUX.A_v_vy)), (

  ((void *)0)

  ), (UNITY_UINT)(33));

   Stats_Find_WDIR_Av();

   UnityAssertFloatsWithin((UNITY_FLOAT)((0.1)), (UNITY_FLOAT)((120.0)), (UNITY_FLOAT)((AUX.WD_Av)), (

  ((void *)0)

  ), (UNITY_UINT)(35));

}



void test_SpStatsIter_WDN(void) {



 Stats_Call_Init();



   do{

    AUX.DSampleDeg = SampleDeg[j_aver];

    SpStats_WD(&j_aver);

       j_aver++;

   } while(j_aver <12);

   Stats_Find_WDIR_Av();



   UnityAssertFloatsWithin((UNITY_FLOAT)((0.1)), (UNITY_FLOAT)((0.6)), (UNITY_FLOAT)((AUX.WD_Av)), (

  ((void *)0)

  ), (UNITY_UINT)(49));

}



void test_SpStatsIter_WDS(void) {

   Stats_Call_Init();

   do{

    AUX.DSampleDeg = SampleDeg2[j_aver];

    SpStats_WD(&j_aver);

       j_aver++;

   } while(j_aver <12);

   Stats_Find_WDIR_Av();



   UnityAssertFloatsWithin((UNITY_FLOAT)((0.1)), (UNITY_FLOAT)((188.0)), (UNITY_FLOAT)((AUX.WD_Av)), (

  ((void *)0)

  ), (UNITY_UINT)(61));

}

#include "unity.h"
#include "stats_CL2_5sp.h"

// Vector global para ensayo cerca de WDIR= Norte (0==360°)
// primeros 2 ignorados
float SampleDeg[] ={
	   0.0,0.0,
	   0.0,0.0,5.0,356.0,2.0,
	   0.0,359.0,5.0,1.0,358.2 };

// Vector global para ensayo cerca de WDIR= SUR (180°)
// primeros 2 ignorados
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
   // TEST_ASSERT_FLOAT WITHIN(delta, expected,actual); 
   TEST_ASSERT_FLOAT_WITHIN(0.1, 0.43301, AUX.A_v_vx);
   TEST_ASSERT_FLOAT_WITHIN(0.1, -0.25, AUX.A_v_vy);
   Stats_Find_WDIR_Av();
   TEST_ASSERT_FLOAT_WITHIN(0.1, 120.0, AUX.WD_Av);
}

void test_SpStatsIter_WDN(void) {
   
	Stats_Call_Init();
   // Leer vector de valores de muestras cerca del N
   do{
	   AUX.DSampleDeg = SampleDeg[j_aver];
	   SpStats_WD(&j_aver); // Computa promedio vector
       j_aver++;
   } while(j_aver <12);
   Stats_Find_WDIR_Av();
   // TEST_ASSERT_FLOAT WITHIN(delta, expected,actual); 
   TEST_ASSERT_FLOAT_WITHIN(0.1, 0.6, AUX.WD_Av);
}

void test_SpStatsIter_WDS(void) {
   Stats_Call_Init();
   do{
	   AUX.DSampleDeg = SampleDeg2[j_aver];
	   SpStats_WD(&j_aver);
       j_aver++;
   } while(j_aver <12);
   Stats_Find_WDIR_Av();
   // TEST_ASSERT_FLOAT WITHIN(delta, expected,actual); 
   TEST_ASSERT_FLOAT_WITHIN(0.1, 188.0, AUX.WD_Av);
}

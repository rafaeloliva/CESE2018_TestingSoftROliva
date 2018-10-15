#include "unity.h"
#include "stats_CL2_5sp.h"



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


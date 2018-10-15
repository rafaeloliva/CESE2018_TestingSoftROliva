#include "build/temp/_test_sp_stats.c"
#include "stats_CL2_5sp.h"
#include "unity.h"


static uint16_t j_aver;



void setUp(void) {

   Stats_Call_Init();

   AUX.DSampleDeg = 120.0;

   AUX.CSampleRho = 1.1;

}



void tearDown(void) {

}



void test_SpStats_WD(void) {



   SpStats_WD(&j_aver);



   TEST_ASSERT_FLOAT WITHIN(0.1, 0.43301, AUX.A_v_vx);

}

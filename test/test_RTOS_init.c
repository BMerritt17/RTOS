#include "RTOS_init.h"
#include "unity.h"


void test_RTOS_Init_should_Set_Systick_Registers_Correctly(void) {


    RTOS_Init();
    TEST_ASSERT_EQUAL_HEX32( ((16000000u / 1000u) - 1u) , SysTick->LOAD);
    TEST_ASSERT_EQUAL_HEX32( 0UL, SysTick->VAL);
    TEST_ASSERT_EQUAL_HEX32( SysTick_CTRL_CLKSOURCE_Msk | 
                             SysTick_CTRL_TICKINT_Msk   |
                             SysTick_CTRL_ENABLE_Msk, SysTick->CTRL);


}

int main() {
    
    UNITY_BEGIN()

    RUN_TEST(test_RTOS_Init_should_Set_Systick_Registers_Correctly);

    return UNITY_END();
}
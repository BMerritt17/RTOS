#include "RTOS_task.h"
#include "unity.h"
#include <stdlib.h>

#define DIMENSION_OF(a) sizeof(a)/a[0]

void helper_FauxTaskFunction(void) {

}

void test_RTOS_create_task_should_HandleTaskCreation(void) {
    
    const int stack_size_bad  = 14; /* Stack requires a minimum len of 15. */
    const int stack_size_good = 40; /* Stack of any acceptable size.       */


    /* Create task stacks (bad and good). */
    uint32_t stack_ftf_bad[stack_size_bad];
    uint32_t stack_ftf_good[stack_size_good];
    
    /* Create task SP.      */
    RTOSThread sp_ftf;

    /* Should return fail,  */
    TEST_ASSERT_EQUAL_INT( TASK_CREATE_FAIL , RTOS_create_task(&sp_ftf, 
        &helper_FauxTaskFunction, stack_ftf_bad, stack_size_bad));
    
    /* Should return pass.  */
    TEST_ASSERT_EQUAL_INT( TASK_CREATE_OK, RTOS_create_task(&sp_ftf, 
        &helper_FauxTaskFunction, stack_ftf_good, stack_size_good));

    /* Initial stack frame. */
    uint32_t result_stack[stack_size_good];

    result_stack[0]  = (1u << 24);                        /* xPSR */
    result_stack[1]  = (uint32_t)helper_FauxTaskFunction; /* PC   */
    result_stack[2]  = 0x0000000Eu;                       /* LR   */
    result_stack[3]  = 0x0000000Cu;                       /* R12  */
    result_stack[4]  = 0x00000003u;                       /* R3   */
    result_stack[5]  = 0x00000002u;                       /* R2   */
    result_stack[6]  = 0x00000001u;                       /* R1   */
    result_stack[7]  = 0x00000000u;                       /* R0   */
    result_stack[8]  = 0x0000000Bu;                       /* R11  */
    result_stack[9]  = 0x0000000Au;                       /* R10  */
    result_stack[10] = 0x00000009u;                       /* R9   */
    result_stack[11] = 0x00000008u;                       /* R8   */
    result_stack[12] = 0x00000007u;                       /* R7   */
    result_stack[13] = 0x00000006u;                       /* R6   */
    result_stack[14] = 0x00000005u;                       /* R5   */
    result_stack[15] = 0x00000004u;                       /* R4   */

    /* Finish initializing stack with 0. */
    for (int i= 16; i < stack_size_good; i++) {
        result_stack[i] = 0;
    }

    /* Test for correct stack initialization. */
    TEST_ASSERT_EQUAL_HEX32_ARRAY(result_stack, stack_ftf_good, stack_size_good);

}



int main() {
    
    UNITY_BEGIN()

    RUN_TEST(test_RTOS_create_task_should_HandleTaskCreation);

    return UNITY_END();
}
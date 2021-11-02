#include "RTOS_task.h"
#include "unity.h"
#include <stdlib.h>

extern RTOS_taskNum; 

void helper_FauxTaskFunction_1(void) {}

void helper_FauxTaskFunction_2(void) {}

void helper_FauxTaskFunction_3(void) {}

void helper_FauxTaskFunction_4(void) {}

void test_RTOS_create_task_should_HandleTaskCreation(void) {
    
    RTOS_taskNum = 0;

    int stack_size_bad = 14;
    int stack_size_good = 20;
    /* Create task stacks (bad and good). */
    uint32_t stack_ftf_bad[stack_size_bad];
    uint32_t stack_ftf_good[stack_size_good];
    
    /* Create task SP.      */
    RTOSThread sp_ftf;

    /* Should return fail,  */
    TEST_ASSERT_EQUAL_INT( TASK_CREATE_FAIL , RTOS_create_task(&sp_ftf, 
        &helper_FauxTaskFunction_1, stack_ftf_bad, stack_size_bad));
    
    /* Should return pass.  */
    TEST_ASSERT_EQUAL_INT( TASK_CREATE_OK, RTOS_create_task(&sp_ftf, 
        &helper_FauxTaskFunction_1, stack_ftf_good, stack_size_good));

    /* Initial stack frame. */
    uint32_t result_stack[stack_size_good];

    result_stack[0]  = (1u << 24);                        /* xPSR */
    result_stack[1]  = (uint32_t)helper_FauxTaskFunction_1; /* PC   */
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
    
    /* SP points to last entry (R4) */
    TEST_ASSERT_EQUAL(&stack_ftf_good[15], sp_ftf.sp);

    /* Verify initializing stack with deadbeef. */
    for (int i= 16; i < stack_size_good; i++) {
        result_stack[i] = 0xDEADBEEFu;
    }

    /* Test for correct stack initialization. */
    TEST_ASSERT_EQUAL_HEX32_ARRAY(result_stack, stack_ftf_good, stack_size_good);

}

void test_RTOS_create_task_should_CreateAndHandleMultipleTasks(void) {

    RTOS_taskNum = 0;
    
    int stack_size_good = 20;
    
    extern RTOS_tasks;

    /* Create task stacks . */
    uint32_t stack_ftf_good_1[stack_size_good];   
    /* Create task SP.      */
    RTOSThread sp_ftf_1;
    /* Should return pass.  */
    TEST_ASSERT_EQUAL_INT( TASK_CREATE_OK, RTOS_create_task(&sp_ftf_1, 
        &helper_FauxTaskFunction_1, stack_ftf_good_1, stack_size_good));


    TEST_ASSERT_EQUAL_INT(1, RTOS_taskNum);


    uint32_t stack_ftf_good_2[stack_size_good];   
    /* Create task SP.      */
    RTOSThread sp_ftf_2;
    /* Should return pass.  */
    TEST_ASSERT_EQUAL_INT( TASK_CREATE_OK, RTOS_create_task(&sp_ftf_2, 
        &helper_FauxTaskFunction_2, stack_ftf_good_2, stack_size_good));


    TEST_ASSERT_EQUAL_INT(2, RTOS_taskNum);


    uint32_t stack_ftf_good_3[stack_size_good];   
    /* Create task SP.      */
    RTOSThread sp_ftf_3;
    /* Should return pass.  */
    TEST_ASSERT_EQUAL_INT( TASK_CREATE_OK, RTOS_create_task(&sp_ftf_3, 
        &helper_FauxTaskFunction_3, stack_ftf_good_3, stack_size_good));


    TEST_ASSERT_EQUAL_INT(3, RTOS_taskNum);


    uint32_t stack_ftf_good_4[stack_size_good];   
    /* Create task SP.      */
    RTOSThread sp_ftf_4;
    /* Should return pass.  */
    TEST_ASSERT_EQUAL_INT( TASK_CREATE_OK, RTOS_create_task(&sp_ftf_4, 
        &helper_FauxTaskFunction_4, stack_ftf_good_4, stack_size_good));


    TEST_ASSERT_EQUAL_INT(4, RTOS_taskNum);

    
    /* Test that tasks counter will catch when too many tasks are created. */
    
    RTOS_taskNum = 33;
    TEST_ASSERT_EQUAL_INT( TASK_CREATE_FAIL, RTOS_create_task(&sp_ftf_1, 
        &helper_FauxTaskFunction_1, stack_ftf_good_1, stack_size_good));



}




int main() {
    
    UNITY_BEGIN()

    RUN_TEST(test_RTOS_create_task_should_HandleTaskCreation);
    RUN_TEST(test_RTOS_create_task_should_CreateAndHandleMultipleTasks);
    
    return UNITY_END();
}
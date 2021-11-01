/******************************************************************************
 * Project  : RTOS
 * File     : RTOS_task.c
 * Notes    : 
 *  Contains functions and variables related to the creation and execution of 
 *  RTOS tasks.
 * 
 * Version  :
 *  (10/31/21) - 1.0
 *      Initial version of file. 
 * 
 *****************************************************************************/

/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include "RTOS_task.h"

/******************************************************************************
 * STATIC FUNCTIONS
 *****************************************************************************/


/******************************************************************************
 * GLOBAL FUNCTIONS
 *****************************************************************************/
int RTOS_create_task(  
    RTOSThread *me,                  /* Stack pointer for task. */
    RTOSThreadHandler threadHandler, /* Task function.          */
    void *stkSto,                    /* Task stack.             */
    uint32_t stkSize) {              /* Size of task stack.     */


    if (stkSize < 15) {

        return TASK_CREATE_FAIL;
    
    }
    


#ifndef _TEST_

#define GROWTH_DIR_1 --
#define GROWTH_DIR_2

    /* Round down the stack top to the 8-byte boundary. NOTE: ARM Cortex-M.. */
    /* ..grows down from hi to low memory.                                   */
    uint32_t *sp = (uint32_t *)((((uint32_t)stkSto + stkSize) / 8) * 8);
    /* Round up the bottom of the stack to the 8-byte boundary               */
    uint32_t *stk_limit = (uint32_t *)(((((uint32_t)stkSto - 1U) / 8) + 1U) * 8);

#else

    /* Setup for testing on host machine                                     */
#define GROWTH_DIR_1
#define GROWTH_DIR_2 ++ 

    uint32_t *sp = stkSto;
    uint32_t *stk_limit = sp + stkSize;

#endif

    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = (1U << 24);              /* xPSR */
    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = (uint32_t)threadHandler; /* PC   */
    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = 0x0000000Eu;             /* LR   */
    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = 0x0000000Cu;             /* R12  */
    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = 0x00000003u;             /* R3   */
    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = 0x00000002u;             /* R2   */
    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = 0x00000001u;             /* R1   */
    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = 0x00000000u;             /* R0   */
    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = 0x0000000Bu;             /* R11  */
    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = 0x0000000Au;             /* R10  */
    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = 0x00000009u;             /* R9   */
    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = 0x00000008u;             /* R8   */
    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = 0x00000007u;             /* R7   */
    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = 0x00000006u;             /* R6   */
    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = 0x00000005u;             /* R5   */
    *(GROWTH_DIR_1 sp GROWTH_DIR_2) = 0x00000004u;             /* R4   */


    /* Finish stack initialization with 0. */
    uint32_t *sp_finish = sp; 

    while(sp_finish != stk_limit) {

        GROWTH_DIR_1 sp_finish GROWTH_DIR_2;
        *(sp_finish) = 0x00000000U;
    
    }

    return TASK_CREATE_OK;

}

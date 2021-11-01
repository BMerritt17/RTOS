/******************************************************************************
 * Project  : RTOS
 * File     : RTOS_task.h
 * Notes    : 
 *  Header containing functions and variables related to the creation and 
 *  execution of RTOS tasks.
 * 
 * Version  :
 *  (10/30/21) - 1.0
 *      Initial version of file. 
 * 
 *****************************************************************************/
#ifndef __RTOS_TASK_H__
#define __RTOS_TASK_H__


/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include "RTOS_init.h"


/******************************************************************************
 * DEFINES
 *****************************************************************************/
#define TASK_CREATE_OK   (0)
#define TASK_CREATE_FAIL (1)

/******************************************************************************
 * STRUCTS
 *****************************************************************************/
typedef struct { /* Thread Control Block (TCB). */
    void *sp; 

} RTOSThread;

/******************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************/
typedef void (*RTOSThreadHandler)();

int RTOS_create_task(RTOSThread *me, RTOSThreadHandler threadHandler,
    void *stkSto, uint32_t stkSize);


#endif /* __RTOS_TASK_H__ */
/*
 * Task_MCAN_Tx.c
 *
 *  Created on: 24 Jan 2026
 *      Author: harik
 */

/*********************************************************************************************************************/
/*--------------------------------------------------Documentation----------------------------------------------------*/
/*********************************************************************************************************************/

/*
 * The task_MCAN_Tx(void *arg) initializes the CAN 0 Node 0 and sends the conv_result_stable value of the EVADC
 * as CAN message.
 *
 */


/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

#include <Level_02_Interfaces/Interface_Libraries/L02_Return_Types.h>
#include <Level_Libraries/iLLD/TC37A/Tricore/Cpu/Std/Platform_Types.h>

/*********************************************************************************************************************/
/*-----------------------------------------------------Externals-----------------------------------------------------*/
/*********************************************************************************************************************/

extern volatile uint16 conv_result_stable;

extern L02_Return_Type IF_MCAN_Init(void);
extern L02_Return_Type IF_MCAN_Send_u16(uint16 value);


/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*
 * function:    task_MCAN_Tx
 * returns:     void
 * parameters:  void
 * description: The MCAN_Tx task initializes the CAN 0 Node 0 and sends the conv_result_stable value of the EVADC
 * as CAN message every 500ms.
 */
void task_MCAN_Tx(void *arg)
{
    IF_MCAN_Init();

    TickType_t lastWakeTime = xTaskGetTickCount();

    while (TRUE)
    {
        IF_MCAN_Send_u16(conv_result_stable);
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(500));
    }

    vTaskDelete(NULL);
}


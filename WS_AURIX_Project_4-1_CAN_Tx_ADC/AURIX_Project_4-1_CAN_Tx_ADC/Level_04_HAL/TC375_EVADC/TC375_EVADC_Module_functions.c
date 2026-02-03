/*
 * TC375_EVADC_Module_functions.c
 *
 *  Created on: 22 Jan 2026
 *      Author: harik
 */

/*********************************************************************************************************************/
/*--------------------------------------------------Documentation----------------------------------------------------*/
/*********************************************************************************************************************/

/*
 * The code in this file shall provide the following functionalities:
 *
 */

/*
 * status: V01.0 2025-12-06
 */


/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/

#include <Level_Libraries/iLLD/TC37A/Tricore/Cpu/Std/Platform_Types.h>
#include <Level_04_HAL/HAL_Libraries/HAL_Return_Types.h>

#include <Level_Libraries/iLLD/TC37A/Tricore/Evadc/Adc/IfxEvadc_Adc.h>

#include <Level_04_HAL/TC375_SCU/TC375_SCU_WDT_functions.h>


/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*
 * function:    Func_DMA_Module_init
 * returns:     HAL_Return_Type Error report
 * parameters:  void
 * description: The function switches on the DMA module of TC375, which hosts all DMA channels.
 */
HAL_Return_Type Func_EVADC_Module_init(void)
{
    HAL_Return_Type tmp_HAL = HAL_E_NOT_OK;
    uint32 tmp_uint32;

    /*
     * Initialization of the EVADC control register CLC to switch on clock
     *
     * field 0: DISR = 0: bit is cleared to 0 to enable the module
     * field 1: DISS: bit is read only, it is a status bit
     * field 2: reserved bit
     * field 3: EDIS = 1: bit is set to 1 to disable sleep mode
     *
     */

    Func_clear_Global_ENDINIT();

    EVADC_CLC.B.DISR = 0x0;
    EVADC_CLC.B.EDIS = 0x1;

    if(EVADC_CLC.B.DISR == 0x0)
    {
        if(EVADC_CLC.B.EDIS == 0x1)
        {
            tmp_HAL = HAL_E_OK;
        }
        else
        {
            tmp_HAL = HAL_E_NOT_OK;
        }
    }
    else
    {
        tmp_HAL = HAL_E_NOT_OK;
    }

    /*
     * do dummy read to finish register setup
     */
    tmp_uint32 = EVADC_CLC.U;

    Func_set_Global_ENDINIT();

    return tmp_HAL;
}



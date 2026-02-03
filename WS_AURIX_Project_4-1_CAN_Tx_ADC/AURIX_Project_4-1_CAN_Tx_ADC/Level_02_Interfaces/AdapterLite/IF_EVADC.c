/*
 * IF_EVADC.c
 *
 *  Created on: 23 Jan 2026
 *      Author: harik
 */


/*********************************************************************************************************************/
/*--------------------------------------------------Documentation----------------------------------------------------*/
/*********************************************************************************************************************/

/*
 * The functionalities in this file belong to the Service Interface Layer of the application.
 * The services build the interface to the functions to control the components on the THD AdapterLite.
 * The functions in this file control the potentiometer on the AdapterLite.
 *
 * The Interface shall provide the functions:
 * 1) initialization of the EVADC Group3
 * 2)
 *
 * EVADC Group3 Channel0 is connected to Port 40.0
 */

/*
 * status: V01.0 2025-12-06
 */


/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/

#include <Level_04_HAL/HAL_Libraries/HAL_Return_Types.h>
#include <Level_02_Interfaces/Interface_Libraries/L02_Return_Types.h>
#include <Level_Libraries/iLLD/TC37A/Tricore/Cpu/Std/Platform_Types.h>

#include <Level_Libraries/iLLD/TC37A/Tricore/Evadc/Adc/IfxEvadc_Adc.h>

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*------------------------------------------------Externals----------------------------------------------------------*/
/*********************************************************************************************************************/

extern HAL_Return_Type Func_EVADC_Module_init(void);

extern HAL_Return_Type Func_EVADC_Group3_init(void);


/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*
 * function:    Func_Adapter_VoltDivider_init
 * returns:     L02_Return_Type error report
 * parameters:  void
 * description: The function initializes the TC375 Port which controls the voltage divider (potentiometer) on the THD AdapterLite
 */
L02_Return_Type Func_Adapter_VoltDivider_init(void)
{
    HAL_Return_Type tmp_HAL;

    tmp_HAL = Func_EVADC_Module_init();

    if(tmp_HAL == HAL_E_OK)
    {
        tmp_HAL = Func_EVADC_Group3_init();
    }

    if(tmp_HAL == HAL_E_OK)
        return L02_E_OK;
    else
        return L02_E_NOT_OK;
}


/*********************************************************************************************************************/
/*
 * function:    Func_EVADC_G3RES0_check
 * returns:     L02_Return_Type error report
 * parameters:  pointer to boolean
 * description: The function checks the Group 3 Result 0 and reports true if the the result of the conversion is valid
 */
L02_Return_Type Func_EVADC_G3RES0_check(boolean *valid)
{

    if (EVADC_G3RES0.B.VF == 0x1)
    {
        *valid = TRUE;
    }
    else
    {
        *valid = FALSE;
    }

    return L02_E_OK;
}


/*********************************************************************************************************************/
/*
 * function:    Func_return_G3C0_conv_result
 * returns:     L02_Return_Type error report
 * parameters:  pointer to uint16
 * description: The function returns the content of the Group 3 Channel 0 conversion result register
 */
L02_Return_Type Func_return_G3C0_conv_result(uint16 *result)
{

    /* Store result */
    *result = (uint16)EVADC_G3RES0.U;

    return L02_E_OK;
}




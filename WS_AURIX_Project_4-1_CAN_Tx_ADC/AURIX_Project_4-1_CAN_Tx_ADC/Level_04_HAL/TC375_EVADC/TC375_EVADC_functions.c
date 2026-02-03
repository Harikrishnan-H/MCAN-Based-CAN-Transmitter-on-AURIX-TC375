/*
 * TC375_EVADC_functions.c
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


/*********************************************************************************************************************/
/*------------------------------------------------------Defines------------------------------------------------------*/
/*********************************************************************************************************************/


/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/


/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/


/*********************************************************************************************************************/
/*
 * function:    Func_EVADC_Group3_init
 * returns:     HAL_Return_Type Error report
 * parameters:  void
 * description: The function initializes the Group3 of the EVADC.
 */
HAL_Return_Type Func_EVADC_Group3_init(void)
{

    HAL_Return_Type tmp_HAL = HAL_E_OK;
    /*
     * Enable the primary/secondary group 3 and prepare it for operation
     */

    /*
     * Analog clock frequency is 160 MHz / 4 = 40 MHz (example)
     * CALSTC = 00
     */
    EVADC_G3ANCFG.U = 0x00300000;

    /*
     * Enable analog block
     */
    EVADC_G3ARBCFG.U = 0x00000003;

    /*
     * Pause for extended wakeup time ( ≥  5 µs)
     */

    /*
     * Begin start-up calibration
     */
    EVADC_GLOBCFG.U = 0x80000000;

    /*
     * Enable arbitration slot 0
     */
    EVADC_G3ARBPR.U = 0x01000000;

    /*
     * Enable request source 0
     */
    EVADC_G3QMR0.U = 0x00000001;

    /*
     * Select 4 clocks for sampletime 4 / 40 MHz = 100 ns
     *
     * The default setting stores results in GxRES0,
     * service requests are issued on GxSR0
     */
    EVADC_G3ICLASS0.U = 0x00000002;

    /*
     * Enable result service requests, if required
     */
    // EVADC_G3RCR0.U = 0x80000000;


    /*
     * Request channel 0 in auto-repeat mode
     */
    EVADC_G3QINR0.U = 0x00000020;

    /*
     * WAIT ;Wait for start-up calibration to complete
     */

    /*
     * ;---> This starts continuous conversion of the channel
     */

    return tmp_HAL;
}



/*
 * TC375_Port_20_functions.c
 *
 *  Created on: 24 Jan 2026
 *      Author: harik
 */

/*********************************************************************************************************************/
/*--------------------------------------------------Documentation----------------------------------------------------*/
/*********************************************************************************************************************/

/*
 * The code in this file shall provide the following functionalities:
 *
 *
 * Connection of MCAN Module 0 CAN Node (Channel) 0 to IO Ports P20.8, P20.7, P20.6
 * MCAN0 Module CAN0 interfaces
 * Signal: TxD    - P20.8
 *         RxDB   - P20.7
 *         STB    - P20.6  - must be driven low to enable transceiver
 *
 * Note: You can use the predefined port addresses in the include file IfxPort_reg.h
 */

/*
 * status: V01.1 2025-12-13
 */

/*********************************************************************************************************************/
/*-----------------------------------------------------Defines-------------------------------------------------------*/
/*********************************************************************************************************************/


/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/

/*
 * IfxPort_reg.h includes the definitions of the Infineon iLLDs for access to ports, peripherals, etc.
 */

#include <Level_04_HAL/HAL_Libraries/HAL_Return_Types.h>

#include <Level_04_HAL/TC375_SCU/TC375_SCU_WDT_functions.h>
#include <Level_Libraries/iLLD/TC37A/Tricore/Cpu/Std/Platform_Types.h>
#include <Level_Libraries/Infra/Sfr/TC37A/_Reg/IfxPort_reg.h>

/*********************************************************************************************************************/
/*-----------------------------------------------------Externals-----------------------------------------------------*/
/*********************************************************************************************************************/



/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/



/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*
 * function:    Func_Port_20_Pin_8_init
 * returns:     HAL_Return_Type error report
 * parameters:  void
 * description: The function initializes Port 20 Pin 8 (P20.8) of TC375 for operation of the CAN0 signal TxD
 */
HAL_Return_Type Func_Port_20_Pin_8_init (void)
{
    HAL_Return_Type tmp;

    /*
     * set P20.8 output to 1
     */
    P20_OMR.B.PCL8 = 0x1;

    /*
     * set P20.8 in IOCR8 register to CAN0 TxD output
     */
    P20_IOCR8.B.PC8 = 0x15;

    if (P20_IOCR8.B.PC8 != 0x15)
    {
        tmp = HAL_E_NOT_OK;
    }
    else
    {
        Func_clear_Global_ENDINIT();

        /*
         * set P20.8 to strong driver / medium edge
         */
        P20_PDR1.B.PD8 = 0x1;

        Func_set_Global_ENDINIT();

        if (P20_PDR1.B.PD8 != 0x1)
        {
            tmp = HAL_E_NOT_OK;
        }
        else
        {
            tmp = HAL_E_OK;
        }
    }

    return tmp;
}


/*********************************************************************************************************************/
/*
 * function:    Func_Port_20_Pin_7_init
 * returns:     HAL_Return_Type error report
 * parameters:  void
 * description: The function initializes Port 20 Pin 7 (P20.7) of TC375 for operation of the CAN0 signal RxDB
 */
HAL_Return_Type Func_Port_20_Pin_7_init (void)
{
    HAL_Return_Type tmp;

    /*
     * set P20.7 in IOCR4 register to CAN0 RxDB input
     */
    P20_IOCR4.B.PC7 = 0x0;

    if (P20_IOCR4.B.PC7 != 0x0)
    {
        tmp = HAL_E_NOT_OK;
    }
    else
    {
        Func_clear_Global_ENDINIT();

        /*
         * set P20.7 to Automotive level input
         */
        P20_PDR0.B.PL7 = 0x0;

        Func_set_Global_ENDINIT();

        if (P20_PDR0.B.PL7 != 0x0)
        {
            tmp = HAL_E_NOT_OK;
        }
        else
        {
            tmp = HAL_E_OK;
        }
    }

    return tmp;
}


/*********************************************************************************************************************/
/*
 * function:    Func_Port_20_Pin_6_init
 * returns:     HAL_Return_Type error report
 * parameters:  void
 * description: The function initializes Port 20 Pin 6 (P20.6) of TC375 for operation of the CAN0 signal STB;
 *              to enable the CAN transceiver the pin must be driven low
 */
HAL_Return_Type Func_Port_20_Pin_6_init (void)
{
    HAL_Return_Type tmp;

    /*
     * set P20.6 in IOCR4 register to general purpose output
     */
    P20_IOCR4.B.PC6 = 0x10;

    if (P20_IOCR4.B.PC6 != 0x10)
    {
        tmp = HAL_E_NOT_OK;
    }
    else
    {
        Func_clear_Global_ENDINIT();

        /*
         * set P20.6 to strong driver / medium edge
         */
        P20_PDR0.B.PD6 = 0x1;

        Func_set_Global_ENDINIT();

        if (P20_PDR0.B.PD6 != 0x1)
        {
            tmp = HAL_E_NOT_OK;
        }
        else
        {
            tmp = HAL_E_OK;
        }
    }

    /*
     * set P20.6 output to 0 (low)
     */
    P20_OMR.B.PCL6 = 0x0;

    return tmp;
}


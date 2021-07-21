/* ***************************************************************** */
/* File name:        aquecedorECooler.c                              */
/* File description: File dedicated to the implementation of the     */
/*                   functions responsible for setting and           */
/*                   controlling the cooler and heater.              */
/*                                                                   */
/* Author name:      Leonardo Vinicius de Souza                      */
/*                   Wallace da Cruz Pereira                         */
/* Creation date:    27apr2021                                       */
/* Revision date:    19jun2021                                                */
/* ***************************************************************** */

#include "board.h"
#include "aquecedorECooler.h"
#include "util.h"
#include "fsl_debug_console.h"

/* Global variables */
float fHeaterDC = 0.00f;
float fCoolerDC = 0.00f;
float fPresetTemperature = 25.00f;

/* ************************************************ */
/* Method name:        PWM_init                     */
/* Method description: Configure the channels 0 and */
/*                     1 of the TPM1 as EdgeAligned */
/*                     PWM, setting the frequency   */
/*                     between 5 and 20Hz.          */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void PWM_init(void)
{
    /*Setting the clock for the TPM1 (SIM_SC5C6-pin 25)*/
    SIM_SCGC6 |= 1<<0x019;
    TPM1_CONF = 0x400C0;

    /*Prescale Factor Selection: Divide by 32*/
    TPM1_SC &= ~(1 << PIN4);	    //set the TPM1_SC pin 4 as 0
    TPM1_SC &= ~(1 << PIN3);
    TPM1_SC |= 0x05;    /*f_pwm = (40MHz)/((0xFFFF + 1)* 32) = 19.07Hz*/

    /*Setting clock (40MHz MCGFLLCLK)*/
    SIM_SOPT2 |= 0x01000000;

    /*LPTPM counter operates in up counting mode. (TPM1_SC-pin5 CPWMS)*/
    TPM1_SC &= ~(1 << PIN5);
    TPM1_SC &= ~(1 << PIN4);
    TPM1_SC |= (1 << PIN3);

    /*Setting max counter value for max resolution*/
    TPM1_CNT = 0x0000;
    TPM1_MOD |= MAX_COUNT;

    /*Channel 0 (Heater): Edge-aligned PWM with High-true pulses (TPM1_C0SC-pins2to5)*/
    TPM1_C0SC &= ~(0xFF);    /*Clear*/
    TPM1_C0SC |= 0x28;

    /*Channel 1 (Cooler): Edge-aligned PWM with High-true pulses (TPM1_C0SC-pins2to5)*/
    TPM1_C1SC &= ~(0xFF);    /*Clear*/
    TPM1_C1SC |= 0x28;
}

/* ************************************************ */
/* Method name:        heater_init                  */
/* Method description: Set the signal PWM on the    */
/*                     pins PTA12.                  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void heater_init(void)
{
    SIM_SCGC5 |= PORT_A;     /*PORTA A*/
    PORTA_PCR12 = MUX_PWM;   /*MUX=011*/
}

/* ************************************************ */
/* Method name:        coolerfan_init               */
/* Method description: Set the signal PWM on the    */
/*                     pins PTA13.                  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void coolerfan_init(void)
{
    SIM_SCGC5 |= PORT_A;    /*PORTA A*/
    PORTA_PCR13 = MUX_PWM;   /*MUX=011*/
}

/* ************************************************ */
/* Method name:        util_genDelay1ms             */
/* Method description: Configure the duty cycle of  */
/*                     the signal PWM.              */
/* Input params:       float fHeaterDuty            */
/* Output params:      n/a                          */
/* ************************************************ */
void heater_PWMDuty()
{
    TPM1_CNT = 0x0000;
    TPM1_C0V = roundNumber(IMAX_COUNT*fHeaterDC);
}

/* ************************************************ */
/* Method name:        setHeater                    */
/* Method description: Configure the global variable*/
/*                     duty cycle of the heater     */
/* Input params:       float fHeaterDuty            */
/* Output params:      n/a                          */
/* ************************************************ */
void setHeater(float fHeaterDuty)
{
    fHeaterDC = fHeaterDuty;
}

/* ************************************************ */
/* Method name:        coolerfan_PWMDuty            */
/* Method description: Configure the duty cycle of  */
/*                     the signal PWM.              */
/* Input params:       float fCoolerDuty            */
/* Output params:      n/a                          */
/* ************************************************ */
void coolerfan_PWMDuty()
{
    TPM1_CNT = 0x0000;
    TPM1_C1V = roundNumber(IMAX_COUNT*fCoolerDC);
}

/* ************************************************ */
/* Method name:        setCooler                    */
/* Method description: Configure the global variable*/
/*                     duty cycle of the cooler     */
/* Input params:       float fCoolerDuty            */
/* Output params:      n/a                          */
/* ************************************************ */
void setCooler(float fCoolerDuty)
{
    fCoolerDC = fCoolerDuty;
}

/* ************************************************ */
/* Method name:        roundNumber                  */
/* Method description: Round a number from float    */
/*                     type to integer type.        */
/* Input params:       float fNumber                */
/* Output params:      integer                      */
/* ************************************************ */
int roundNumber(float fNumber)
{
    return (int)(fNumber + 0.5);
}

/* ************************************************ */
/* Method name:        getHeaterDuty                */
/* Method description: Return the value of duty     */
/*                     cycle of the Heater.         */
/* Input params:       n/a                          */
/* Output params:      float fNumber                */
/* ************************************************ */
float getHeaterDuty(void)
{
    return fHeaterDC;
}

/* ************************************************ */
/* Method name:        getCoolerDuty                */
/* Method description: Return the value of Dutty    */
/*                     cycle of the Cooler.         */
/* Input params:       n/a                          */
/* Output params:      float fNumber                */
/* ************************************************ */
float getCoolerDuty(void)
{
    return fCoolerDC;
}

/* ************************************************ */
/* Method name:        getPresetTemp                */
/* Method description: Return the value of preset   */
/*                     of the temperature.           */
/* Input params:       n/a                          */
/* Output params:      float fNumber                */
/* ************************************************ */
float getPresetTemp(void)
{
    return fPresetTemperature;
}

/* ************************************************ */
/* Method name:        setPresetTemp                */
/* Method description: Configure the global variable*/
/*                     preset of the temperature    */
/* Input params:       float fPreSet                */
/* Output params:      n/a                          */
/* ************************************************ */
void setPresetTemp(float fPreSet)
{
    fPresetTemperature = fPreSet;
}

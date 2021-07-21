/* ***************************************************************** */
/* File name:        tacometro.c                                     */
/* File description: File dedicated to the implementation of the     */
/*                   functions responsible for configuring and       */
/*                   read the tachometer.                            */
/*                                                                   */
/* Author name:      Leonardo Vinicius de Souza                      */
/*                   Wallace da Cruz Pereira                         */
/* Creation date:    08may2021                                       */
/* Revision date:    19jun2021                                       */
/* ***************************************************************** */

/*includes*/
#include "board.h"
#include "tacometro.h"

/* global variable*/
int uiT = 0; /* Speed of the Cooler */

/* ************************************************ */
/* Method name:        tachometer_init              */
/* Method description: Configure the tachometer to  */
/*                     receive an external clock.   */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void tachometer_init(void)
{
	/*Setting the clock for the TPM1 (SIM_SC5C6-pin 24)*/
	SIM_SCGC6 |= 0x01000000;

	/*Setting pin PTE29 as external clock (FTM_CLKIN0 - Alternative 4)*/
	SIM_SCGC5 |= 0x2000;
	PORTE_PCR29 = 0x400;

	/*Prescale Factor Selection: cmod = 10 */
	TPM0_SC &= ~(0xFFFFFFFF);    /*Clear*/
	TPM0_SC |= 0x10;

	/*Setting external pin TPM0 pin 24*/
	SIM_SOPT4 &= ~(0x01000000);

	/*Setting max counter value*/
	TPM0_CNT = 0;
	TPM0_MOD |= 0xFFFF;

	/*Channel 0 : input capture, Capture on Rising Edge Only*/
	TPM0_C0SC &= 0;    /*Clear*/
	TPM0_C0SC |= 4;
}

/* ***************************************************** */
/* Method name:        tachometer_readSensor             */
/* Method description: Fan speed reading (RPM).          */
/*                                                       */
/* Input params:       unsigned int uiPeriod in ms       */
/* Output params:      Cooler speed in RPM               */
/* ***************************************************** */
unsigned int tachometer_readSensor(unsigned int uiPeriod)
{
	int aux = TPM0_CNT;
	float f = (float)aux/(7*uiPeriod);
	uiT = 60*f*1000;
	TPM0_CNT = 0;
	return(uiT);
}

/* ***************************************************** */
/* Method name:        getCoolerSpeed                    */
/* Method description: Returns the global variable uiT.  */
/*                                                       */
/* Input params:       n/a                               */
/* Output params:      unsigned int uiT                  */
/* ***************************************************** */
unsigned int getCoolerSpeed()
{
	return(uiT);
}

/* ***************************************************************** */
/* File name:        main.c                                          */
/* File description: File dedicated to the ES670 prototype projects  */
/*                   involving the FRDM-KL25Z board together with is */
/*                   daughter board containing more peripherals      */
/*                                                                   */
/*                   Processor MKL25Z128VLK4 characteristics         */
/*                   48 MHz ARM Cortex-M0+ core                      */
/*                   128 KB program flash memory                     */
/*                   16 KB SRAM                                      */
/*                   Voltage range: 1.71 to 3.6 V                    */
/*                                                                   */
/* Author name:      Rodrigo M Bacurau                               */
/* Creation date:    26fev2020                                       */
/* Revision date:    19jun2021                                       */
/* ***************************************************************** */

/* includes */
#include "util.h"
#include "mcg.h"
#include "UART.h"
#include "lcd.h"
#include "adc.h"
#include "aquecedorECooler.h"
#include "lptmr.h"
#include "util.h"
#include "fsl_debug_console.h"
#include "tacometro.h"
#include "pid.h"
#include "ledrgb.h"

/* global variables */
unsigned int uiV;
int iCont = 0;
int jCont = 0;

/* ************************************************ */
/* Method name:        interruption                 */
/* Method description: treatment of interruption    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void interruption(void)
{
	/* Control PID */
	setHeater(pidUpdateData(adc_getTemperature(), (float)getPresetTemp()));
	heater_PWMDuty();
	coolerfan_PWMDuty();

	iCont++;
	/* LCD interruption */
	if(iCont == 15)
	{
		lcd_writeLCD();
		iCont = 0;
	}
	jCont++;
	/* Tacometer interruption */
	if(jCont == 2)
	{
		uiV = tachometer_readSensor(200);
		jCont = 0;
	}
}

/* ************************************************ */
/* Method name:        boardInit                    */
/* Method description: main board all needed        */
/*                     initializations              */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void boardInit(void)
{
	/* fist of all, clock configuration and initialization */
	mcg_clockInit();

	/* initialization of Led RGB */
	ledrgb_init();

    /* initialization of UART module */
	UART0_init();

	/* enable the interruption */
	UART0_enableIRQ();

	/* initialization of lcd */
	lcd_initLcd();

	/* initialization of PWM module */
	PWM_init();

	/* initialization of heater */
	heater_init();

	/* initialization of cooler */
	coolerfan_init();

	tachometer_init();

	/* initialization of adc module */
	adc_initADCModule();

	/* initialization of PID */
	pid_init();

	/* timer lptmr with 100ms*/
	tc_installLptmr0(100000, interruption);
}

/* ************************************************ */
/* Method name:        main                         */
/* Method description: system entry point           */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
int main(void)
{
	/* board initializations */
	boardInit();

	/* main loop */
    while(1){}
}

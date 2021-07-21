/* ***************************************************************** */
/* File name:        communicationStateMachine.c                     */
/* File description: Implements the functions used to configure and  */
/*                   set the state machine.                          */
/*                                                                   */
/* Author name:      Wallace da Cruz Pereira                         */
/*                   Leonardo Vinicius de Souza                      */
/* Creation date:    22may2021                                       */
/* Revision date:    19jun2021                                       */
/* ***************************************************************** */

/* includes */
#include "communicationStateMachine.h"
#include "fsl_debug_console.h"
#include "util.h"
#include "aquecedorECooler.h"
#include "lcd.h"
#include "pid.h"
#include "adc.h"

/* definitions */
#define IDDLE    '0'
#define READY    '1'
#define GET      '2'
#define SET      '3'
#define B_VALUE  '4'
#define F_VALUE  '5'
#define PRINT    '6'
#define K        '7'
#define I_VALUE  '8'

/* global variables*/
typedef struct {
	unsigned char ucState;
	unsigned char ucValue[8];
	unsigned char ucCount;
	unsigned char ucParam;
}communication;
communication params = {.ucState = IDDLE, .ucCount = 0};
int iButtons = 0;
int iSeg = 0;

/* ************************************************ */
/* Method name: uartCommunicationMachineState  		*/
/* Method description: This function executes the   */
/*                     machine state.               */
/* Input params:	   unsigned char ucData         */
/* Output params:	   n/a 							*/
/* ************************************************ */
void UartCommunicationStateMachine(unsigned char ucData)
{
	if (ucData == '#')
	{
		params.ucState = READY;
	} else {
		switch (params.ucState)
		{
		/* initial state */
		case IDDLE:
			break;

		/* second state */
		case READY:
			switch (ucData)
			{
			case 'g': /* get */
				params.ucState = GET;
				break;
			case 's': /* set */
				params.ucState = SET;
				break;
			default:
			    params.ucCount = 0;
			    params.ucState = IDDLE;
			}
			break;
		/* third state */
		case GET:
			/*
			 * c = cooler duty
			 * h = heater duty
			 * t = preset temperature
			 * b = bottons
			 * q = real temperature
			 * l = lcd
			 * s = 7 segments display
			 */
			if (ucData == 'c' || ucData == 'h' || ucData == 't' || ucData == 'b' || ucData == 'q' || ucData == 'l'|| ucData == 's')
			{
				params.ucParam = ucData;
				params.ucState = PRINT;

			} else if (ucData == 'k') /* k = PID parameters*/
			{
				params.ucParam = 'g';
				params.ucState = K;
			} else {
				params.ucState = IDDLE;
				params.ucCount = 0;
			}
			break;
		/* fourth state */
		case SET:
			if (ucData == 'c' || ucData == 'h' || ucData == 't')
			{
				params.ucParam = ucData;
				params.ucState = F_VALUE;
			} else if (ucData == 'k') {
				params.ucState = K;
				params.ucParam = 's';
			} else if (ucData == 'b' || ucData == 'l' || ucData == 's') {

				params.ucParam = ucData;
				params.ucState = B_VALUE;
			} else {
			    params.ucState = IDDLE;
			    params.ucCount = 0;
			}
			break;
		/*configures binary variables*/
		case B_VALUE:
			switch (ucData)
			{
			case '0':
				params.ucValue[0] = '0';
				params.ucCount++;
				break;
			case '1':
				params.ucValue[0] = '1';
				params.ucCount++;
				break;
			case ';':
				if (params.ucCount == 1)
				{
					setBinaryParameter();
					params.ucCount = 0;
					params.ucState = IDDLE;
				} else {
					params.ucCount = 0;
					params.ucState = IDDLE;
				}
				break;
			default:
				params.ucState = IDDLE;
				params.ucCount = 0;
			}

			if (params.ucCount > 1)
			{
				params.ucState = IDDLE;
				params.ucCount = 0;
			}
			break;
		/*configures float variables*/
		case F_VALUE:
			if ((ucData >= '0' && ucData <= '9') || ucData == '.')
			{
				params.ucValue[params.ucCount] = ucData;
				params.ucCount++;
				if (params.ucCount > 5)
				{
					params.ucState = IDDLE;
					params.ucCount = 0;
				}
				break;
			}
			if (params.ucCount != 0 && ucData == ';') {
				params.ucValue[params.ucCount] = '\0';
				setFloatParameter();
				params.ucCount = 0;
				params.ucState = IDDLE;
				break;
			}
			params.ucCount = 0;
			params.ucState = IDDLE;
			break;
		/* configures PID parameters */
		case K:
			if (ucData == 'p' || ucData == 'i' || ucData == 'd')
			{
				if (params.ucParam == 's') {
					params.ucParam = ucData;
					params.ucState = F_VALUE;
				} else if (params.ucParam == 'g') {
					params.ucParam = ucData;
					params.ucState = PRINT;
				}
				break;
			}
			params.ucCount = 0;
			params.ucState = IDDLE;
			break;
		/* configures get cases */
		case PRINT:
			if (ucData == ';')
			{
				getData();
			}
		    params.ucState = IDDLE;
            break;
        }
    }
}


/* ******************************************************** */
/* Method name: 	   setBinaryParameter()	         		*/
/* Method description: set the value to a binary variable   */
/* Input params:	   n/a                                  */
/* Output params:	   n/a 							        */
/* ******************************************************** */
void setBinaryParameter() {
	int iAux;
	if (params.ucValue[0] == '1')
	{
	    iAux = 1;
	} else {
	    iAux = 0;
	}
    switch(params.ucParam)
	{
    case 'b':
    	iButtons = iAux;
    	break;
    case 'l':
    	lcd_setIMOD(iAux);
    	break;
    case 's':
    	iSeg = iAux;
        break;
	}
}

/* ******************************************************* */
/* Method name: 	   setFloatParameter	           	   */
/* Method description: set the value to a float variable   */
/* Input params:	   n/a                                 */
/* Output params:	   n/a 							       */
/* ******************************************************* */
void setFloatParameter()
{
	float fAux = string2FloatB(params.ucValue); /* Float format xx.xx */
	float fAux2 = string2Float(params.ucValue); /* Float format x.xx */
	switch(params.ucParam)
	{
	/* set heater */
	case 'h':
		if (params.ucValue[1] != '.') {
			debug_putchar('E');
			debug_putchar('r');
			debug_putchar('r');
			debug_putchar('o');
			debug_putchar(' ');
		}
		setHeater(fAux2);
		heater_PWMDuty();
		getData();
        break;
    /* set cooler */
	case 'c':
		if (params.ucValue[1] != '.') {
			debug_putchar('E');
			debug_putchar('r');
			debug_putchar('r');
			debug_putchar('o');
			debug_putchar(' ');
		}
		setCooler(fAux2);
		coolerfan_PWMDuty();
		getData();
		break;
	/* set preset temperature */
	case 't':
		if (params.ucValue[2] != '.') {
			debug_putchar('E');
			debug_putchar('r');
			debug_putchar('r');
			debug_putchar('o');
			debug_putchar(' ');
		}
		if(fAux < 60.00){
			setPresetTemp(fAux);
		} else {
			debug_putchar('E');
			debug_putchar('r');
			debug_putchar('r');
			debug_putchar('o');
			debug_putchar(' ');
			debug_putchar('T');
			debug_putchar('>');
			debug_putchar('6');
			debug_putchar('0');
			debug_putchar(' ');
		}
		getData();
		break;
	/* set Kp */
	case 'p':
		if (params.ucValue[2] != '.') {
			debug_putchar('E');
			debug_putchar('r');
			debug_putchar('r');
			debug_putchar('o');
			debug_putchar(' ');
		}
		pid_setKp(fAux);
		getData();
        break;
    /* set Ki */
	case 'i':
		if (params.ucValue[2] != '.') {
			debug_putchar('E');
			debug_putchar('r');
			debug_putchar('r');
			debug_putchar('o');
			debug_putchar(' ');
		}
		pid_setKi(fAux);
		getData();
		break;
	/* set Kd */
	case 'd':
		if (params.ucValue[2] != '.') {
			debug_putchar('E');
			debug_putchar('r');
			debug_putchar('r');
			debug_putchar('o');
			debug_putchar(' ');
		}
		pid_setKd(fAux);
		getData();
		break;
	}
}

/* *************************************************** */
/* Method name: 	   getData()	                   */
/* Method description: returns the requested value     */
/* Input params:	   n/a                             */
/* Output params:	   n/a 							   */
/* *************************************************** */
void getData()
{
	char cAux[10];
	switch(params.ucParam)
	{
	/* Bottons */
	case'b':
		if (iButtons == 1)
		{
			debug_putchar('b');
			debug_putchar(':');
			debug_putchar('o');
		    debug_putchar('n');
		    debug_putchar('\n');
		    debug_putchar('\r');
		} else {
			debug_putchar('b');
			debug_putchar(':');
			debug_putchar(' ');
			debug_putchar('o');
			debug_putchar('f');
			debug_putchar('f');
			debug_putchar('\n');
			debug_putchar('\r');
		}
		break;
	/* 7 segments display */
	case's':
		if (iButtons == 1)
		{
			debug_putchar('s');
			debug_putchar(':');
			debug_putchar(' ');
			debug_putchar('o');
		    debug_putchar('n');
		    debug_putchar('\n');
		    debug_putchar('\r');
		} else {
			debug_putchar('s');
			debug_putchar(':');
			debug_putchar(' ');
			debug_putchar('o');
			debug_putchar('f');
			debug_putchar('f');
			debug_putchar('\n');
			debug_putchar('\r');
		}
		break;
	/* lcd */
	case'l':
		if (getIMode() == 1)
		{
			debug_putchar('l');
			debug_putchar('c');
			debug_putchar('d');
			debug_putchar(':');
			debug_putchar(' ');
			debug_putchar('1');
		    debug_putchar('\n');
			debug_putchar('\r');
		} else {
			debug_putchar('l');
			debug_putchar('c');
			debug_putchar('d');
			debug_putchar(':');
			debug_putchar(' ');
			debug_putchar('0');
		    debug_putchar('\n');
			debug_putchar('\r');
		}
		break;
	/* cooler duty cycle */
	case 'c':
		float2Str(getCoolerDuty(), cAux);
		debug_putchar('c');
		debug_putchar(':');
		debug_putchar(' ');
	    for(int i = 1; i < 5; i++)
	    {
	    	if (cAux[i] == '\0') break;
	    	debug_putchar(cAux[i]);
	    }
	    debug_putchar('\n');
	    debug_putchar('\r');
	    break;
	/* heater duty cycle */
	case 'h':
		float2Str(getHeaterDuty(), cAux);
		debug_putchar('h');
		debug_putchar(':');
		debug_putchar(' ');
		for(int i = 1; i < 5; i++)
		{
	        if (cAux[i] == '\0') break;
			debug_putchar(cAux[i]);
	    }
		debug_putchar('\n');
		debug_putchar('\r');
	    break;
	/* Kp */
	case 'p':
		float2Str(pid_getKp(), cAux);
		 debug_putchar('k');
		 debug_putchar('p');
		 debug_putchar(':');
		 debug_putchar(' ');
		 for(int i = 0; i < 10; i++)
		 {
		     if (cAux[i] == '\0') break;
		 	 debug_putchar(cAux[i]);
		 }
		 debug_putchar('\n');
		 debug_putchar('\r');
		 break;
	/* Ki */
	case 'i':
		float2Str(pid_getKi(), cAux);
		 debug_putchar('k');
		 debug_putchar('i');
		 debug_putchar(':');
		 debug_putchar(' ');
		 for(int i = 0; i < 10; i++)
		 {
		     if (cAux[i] == '\0') break;
		 	 debug_putchar(cAux[i]);
		 }
		 debug_putchar('\n');
		 debug_putchar('\r');
		 break;
	/* Kd */
	case 'd':
		float2Str(pid_getKd(), cAux);
		 debug_putchar('k');
		 debug_putchar('d');
		 debug_putchar(':');
		 debug_putchar(' ');
		 for(int i = 0; i < 10; i++)
		 {
		     if (cAux[i] == '\0') break;
		 	 debug_putchar(cAux[i]);
		 }
		 debug_putchar('\n');
		 debug_putchar('\r');
		 break;
	/* Preset Temperature */
	case 't':
		float2Str(getPresetTemp(), cAux);
		debug_putchar('T');
		debug_putchar('p');
		debug_putchar(':');
		debug_putchar(' ');
		for(int i = 0; i < 5; i++)
		{
	        if (cAux[i] == '\0') break;
			debug_putchar(cAux[i]);
	    }
		debug_putchar('\n');
		debug_putchar('\r');
	    break;
	/* Real time Temperature */
	case 'q':
		float2Str(adc_getTemperature(), cAux);
		debug_putchar('T');
		debug_putchar(':');
		debug_putchar(' ');
		for(int i = 0; i < 10; i++)
			{
		       if (cAux[i] == '\0') break;
			debug_putchar(cAux[i]);
		    }
		debug_putchar('\n');
		debug_putchar('\r');
		break;
    }
}


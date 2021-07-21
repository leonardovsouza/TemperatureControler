/* ***************************************************************** */
/* File name:        pid.c                                           */
/* File description: This file has a couple of useful functions to   */
/*                   control the implemented PID controller          */
/* Author name:      julioalvesMS, IagoAF, rBacurau                  */
/* Creation date:    21jun2018                                       */
/* Revision date:    19jun2021                                       */
/* ***************************************************************** */

#include "pid.h"
#include "ledrgb.h"
#include "board.h"

pid_data_type pidConfig;

/* ************************************************ */
/* Method name:        pid_init                     */
/* Method description: Initialize the PID controller*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void pid_init(void)
{
	pidConfig.fKp = 12.00;
	pidConfig.fKd = 0.10;
	pidConfig.fKi = 0.01;
	pidConfig.fError_previous = 0;
	pidConfig.fError_sum = 0.0;
	pidConfig.fOut = 0.00;
}


/* ************************************************** */
/* Method name:        pid_setKp                      */
/* Method description: Set a new value for the PID    */
/*                     proportional constant          */
/* Input params:       fKp: New value                 */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_setKp(float fKp)
{
	pidConfig.fKp = fKp;
}


/* ************************************************** */
/* Method name:        pid_getKp                      */
/* Method description: Get the value from the PID     */
/*                     proportional constant          */
/* Input params:       n/a                            */
/* Output params:      float: Value                   */
/* ************************************************** */
float pid_getKp(void)
{
	return pidConfig.fKp;
}


/* ************************************************** */
/* Method name:        pid_setKi                      */
/* Method description: Set a new value for the PID    */
/*                     integrative constant           */
/* Input params:       fKi: New value                 */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_setKi(float fKi)
{
	pidConfig.fKi = fKi;
}


/* ************************************************** */
/* Method name:        pid_getKi                      */
/* Method description: Get the value from the PID     */
/*                     integrative constant           */
/* Input params:       n/a                            */
/* Output params:      float: Value                   */
/* ************************************************** */
float pid_getKi(void)
{
	return pidConfig.fKi;
}


/* ************************************************** */
/* Method name:        pid_setKd                      */
/* Method description: Set a new value for the PID    */
/*                     derivative constant            */
/* Input params:       fKd: New value                 */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_setKd(float fKd)
{
	pidConfig.fKd = fKd;
}


/* ************************************************** */
/* Method name:        pid_getKd                      */
/* Method description: Get the value from the PID     */
/*                     derivative constant            */
/* Input params:       n/a                            */
/* Output params:      float: Value                   */
/* ************************************************** */
float pid_getKd(void)
{
	return pidConfig.fKd;
}

/* ************************************************** */
/* Method name:        pid_updateData                 */
/* Method description: Update the control output      */
/*                     using the reference and sensor */
/*                     value                          */
/* Input params:       fSensorValue: Value read from  */
/*                     the sensor                     */
/*                     fReferenceValue: Value used as */
/*                     control reference              */
/* Output params:      float: New Control effort     */
/* ************************************************** */
float pidUpdateData(float fSensorValue, float fSetValue)
{
	float fError, fDifference;
	fError = fSetValue - fSensorValue;

	/* Case the temperature of the system is equal to set value */
	if ((-01.00f <= fError) && (fError <= 01.00f)){
		ledrgb_write(4);
	} else {
		ledrgb_write(0);
	}

	/* Solving the problem of saturation */
	if((pidConfig.fOut != 1.00) | (pidConfig.fOut != 0.00))
	{
		pidConfig.fError_sum += fError;
	}
	fDifference = pidConfig.fError_previous - fError;

	pidConfig.fOut = pidConfig.fKp*fError
		 + pidConfig.fKi*pidConfig.fError_sum
		 + pidConfig.fKd*fDifference;

	pidConfig.fError_previous = fError;

	pidConfig.fOut = pidConfig.fOut/100;

	if (pidConfig.fOut>1.0)
		pidConfig.fOut = 1.00;

	else if (pidConfig.fOut<0.0)
		pidConfig.fOut = 0.00;

	return pidConfig.fOut;
}

/* ***************************************************************** */
/* File name:        communicationStateMachine.h                     */
/* File description: Header file containing the prototypes of the    */
/*                   functions used to configure and set the         */
/*                   state machine.                                  */
/*                                                                   */
/* Author name:      Wallace da Cruz Pereira                         */
/*                   Leonardo Vinicius de Souza                      */
/* Creation date:    23may2021                                       */
/* Revision date:    19jun2021                                       */
/* ***************************************************************** */

#ifndef SOURCES_COMMUNICATIONSTATEMACHINE_H_
#define SOURCES_COMMUNICATIONSTATEMACHINE_H_

/* ******************************************************** */
/* Method name: 	   setBinaryParameter()	         		*/
/* Method description: set the value to a binary variable   */
/* Input params:	   n/a                                  */
/* Output params:	   n/a 							        */
/* ******************************************************** */
void setBinaryParameter(void);

/* ******************************************************* */
/* Method name: 	   setFloatParameter	           	   */
/* Method description: set the value to a float variable   */
/* Input params:	   n/a                                 */
/* Output params:	   n/a 							       */
/* ******************************************************* */
void setFloatParameter(void);

/* ******************************************************* */
/* Method name: 	   getData()	                       */
/* Method description: returns the requested value         */
/* Input params:	   n/a                                 */
/* Output params:	   n/a 							       */
/* ******************************************************* */
void getData();

/* ******************************************************* */
/* Method name: uartCommunicationMachineState  		       */
/* Method description: This function executes the          */
/*                     machine state.                      */
/* Input params:	   unsigned char ucData                */
/* Output params:	   n/a 							       */
/* ******************************************************* */
void UartCommunicationStateMachine(unsigned char ucData);


#endif /* SOURCES_COMMUNICATIONSTATEMACHINE_H_ */

/* ***************************************************************** */
/* File name:        tacometro.h                                     */
/* File description: Header file containing the prototypes of the    */
/*                   functions used to configure and set the         */
/*                   tachometer                                      */
/*                                                                   */
/* Author name:      Leonardo Vinicius de Souza                      */
/*                   Wallace da Cruz Pereira                         */
/* Creation date:    08may2021                                       */
/* Revision date:    19jun2021                                       */
/* ***************************************************************** */

#ifndef SOURCES_TACOMETRO_H_
#define SOURCES_TACOMETRO_H_

/* ************************************************ */
/* Method name:        tachometer_init              */
/* Method description: Configure the tachometer to  */
/*                     receive an external clock.   */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void tachometer_init(void);

/* ***************************************************** */
/* Method name:        tachometer_readSensor             */
/* Method description: Fan speed reading (RPM).          */
/*                                                       */
/* Input params:       unsigned int uiPeriod in ms       */
/* Output params:      Cooler speed in RPM               */
/* ***************************************************** */
unsigned int tachometer_readSensor(unsigned int uiPeriod);

/* ***************************************************** */
/* Method name:        getCoolerSpeed                    */
/* Method description: Returns the global variable uiT.  */
/*                                                       */
/* Input params:       n/a                               */
/* Output params:      unsigned int uiT                  */
/* ***************************************************** */
unsigned int getCoolerSpeed();

#endif /* SOURCES_TACOMETRO_H_ */

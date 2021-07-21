/* ***************************************************************** */
/* File name:        display7seg.h                                   */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for the display 7seg                 */
/*                   from the FRDM-KL25Z board                       */
/* Author name:      Wallace da Cruz Pereira                         */
/*                   Leonardo Vinicius de Souza                      */
/* Creation date:    21apr2021                                       */
/* Revision date:    21apr2021                                       */
/* ***************************************************************** */

#ifndef SOURCES_DISPLAY7SEG_H_
#define SOURCES_DISPLAY7SEG_H_

/* ********************************************************* */
/* Method name:        initDisplay7seg                       */
/* Method description: Initialize the 7seg display function  */
/* Input params:       n/a                                   */
/* Output params:      n/a                                   */
/* ********************************************************* */
void initDisplay7seg(void);

/* ****************************************************** */
/* Method name:        display7seg_writeSymbol            */
/* Method description: Write data to be displayed         */
/* Input params:      ucDisplay => Number of display      */
/*                    ucValue => Number to be written     */
/* Output params:      n/a                                */
/* ****************************************************** */
void display7seg_writeSymbol(unsigned char ucDisplay, unsigned char ucValue);

#endif /* SOURCES_DISPLAY7SEG_H_ */
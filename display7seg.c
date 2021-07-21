/* ***************************************************************** */
/* File name:        display7seg.c                                   */
/* File description: This file has a couple of useful functions to   */
/*                   write and use the display 7 segments            */
/*                                                                   */
/* Author name:      Wallace da Cruz Pereira                         */
/*                   Leonardo Vinicius de Souza                      */
/* Creation date:    21apr2021                                       */
/* Revision date:    21apr2021                                       */
/* ***************************************************************** */

#include "board.h"
#include "util.h"
#include "display7seg.h"

/* system includes */
#include "fsl_clock_manager.h"

/* ********************************************************* */
/* Method name:        initDisplay7seg                       */
/* Method description: Initialize the 7seg display function  */
/* Input params:       n/a                                   */
/* Output params:      n/a                                   */
/* ********************************************************* */
void initDisplay7seg(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= PORTC_IDX;

    /* set pin as gpio */
    PORTC_PCR0 |= SET_AS_GPIO;
    PORTC_PCR1 |= SET_AS_GPIO;
    PORTC_PCR2 |= SET_AS_GPIO;
    PORTC_PCR3 |= SET_AS_GPIO;
    PORTC_PCR4 |= SET_AS_GPIO;
    PORTC_PCR5 |= SET_AS_GPIO;
    PORTC_PCR6 |= SET_AS_GPIO;
    PORTC_PCR7 |= SET_AS_GPIO;
    PORTC_PCR8 |= SET_AS_GPIO;
    PORTC_PCR9 |= SET_AS_GPIO;
    PORTC_PCR10 |= SET_AS_GPIO;
    PORTC_PCR11 |= SET_AS_GPIO;
    PORTC_PCR12 |= SET_AS_GPIO;
    PORTC_PCR13 |= SET_AS_GPIO;


    /* set pin as digital output */
    for (int i = 0; i < 14; i++) {
        GPIOC_PDDR |= 1 << i;
    }
}

void display7seg_setSymbol(unsigned char ucValue)
{
	switch (ucValue)
		{
	        case 0:
			    GPIOC_PDOR &= CHAR_ERASE;
			    GPIOC_PDOR |= CHAR_0;
			    break;
		    case 1:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_1;
		    	break;
		    case 2:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_2;
		    	break;
		    case 3:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_3;
		    	break;
		    case 4:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_4;
		    	break;
		    case 5:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_5;
		    	break;
		    case 6:
		    	GPIOC_PDOR &= CHAR_ERASE;
		        GPIOC_PDOR |= CHAR_6;
		    	break;
		    case 7:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_7;
		    	break;
		    case 8:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_8;
		    	break;
		    case 9:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_9;
		    	break;
		    case 10:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_0p;
		    	break;
		    case 11:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_1p;
		    	break;
		    case 12:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_2p;
		    	break;
		    case 13:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_3p;
		    	break;
		    case 14:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_4p;
		    	break;
		    case 15:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_5p;
		    	break;
		    case 16:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_6p;
		    	break;
		    case 17:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_7p;
		        break;
		    case 18:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_8p;
		    	break;
		    case 19:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_9p;
		    	break;
		    case 20:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_Vp;
		    	break;
		    case 21:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	break;
		    case 22:
		    	GPIOC_PDOR &= CHAR_ERASE;
		    	GPIOC_PDOR |= CHAR_ALL;
		    	break;

		}
}

/* ****************************************************** */
/* Method name:        display7seg_writeSymbol            */
/* Method description: Write data to be displayed         */
/* Input params:      ucDisplay => Number of display      */
/*                    ucValue => Number to be written     */
/* Output params:      n/a                                */
/* ****************************************************** */
void display7seg_writeSymbol(unsigned char ucDisplay, unsigned char ucValue)
{
	GPIOC_PDOR &= 0xFFFFC3FF;
	switch (ucDisplay)
	{
	    case 1:
	    	GPIOC_PDOR |= (1u << DISP_1);
	    	display7seg_setSymbol(ucValue);
	    	break;
	    case 2:
	    	GPIOC_PDOR |= (1u << DISP_2);
	    	display7seg_setSymbol(ucValue);
	    	break;
	    case 3:
	    	GPIOC_PDOR |= (1u << DISP_3);
	    	display7seg_setSymbol(ucValue);
	    	break;
	    case 4:
	    	GPIOC_PDOR |= (1u << DISP_4);
	    	display7seg_setSymbol(ucValue);
	    	break;
	}
}

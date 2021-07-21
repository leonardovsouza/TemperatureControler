/* ***************************************************************** */
/* File name:        util.c                                          */
/* File description: This file has a couple of useful functions to   */
/*                   make programming more productive                */
/*                                                                   */
/*                   Remarks: The soft delays consider               */
/*                   core clock @ 40MHz                              */
/*                   bus clock @ 20MHz                               */
/*                                                                   */
/* Author name:      dloubach                                        */
/* Creation date:    09jan2015                                       */
/* Revision date:    19jun2021                                       */
/* ***************************************************************** */

#include "util.h"

/* ************************************************ */
/* Method name:        util_genDelay088us           */
/* Method description: generates ~ 088 micro sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay088us(void)
{
    char i;
    for(i=0; i<120; i++)
    {
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
    }
}

/* ************************************************ */
/* Method name:        util_genDelay250us           */
/* Method description: generates ~   250 micro sec  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay250us(void)
{
    char i;
    for(i=0; i<120; i++)
    {
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
    }
    util_genDelay088us();
    util_genDelay088us();
}



/* ************************************************ */
/* Method name:        util_genDelay1ms             */
/* Method description: generates ~   1 mili sec     */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay1ms(void)
{
    util_genDelay250us();
    util_genDelay250us();
    util_genDelay250us();
    util_genDelay250us();
}


/* ************************************************ */
/* Method name:        util_genDelay10ms            */
/* Method description: generates ~   10 mili sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay10ms(void)
{
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
}



/* ************************************************ */
/* Method name:        util_genDelay100ms           */
/* Method description: generates ~   100 mili sec   */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay100ms(void)
{
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
}

/* ************************************************ */
/* Method name:        float2Str                    */
/* Method description: Converts a float type (format*/
/*                      XX.XX) in a struct.         */
/* Input params:       float n = float number       */
/*                     char* str = struct           */
/* Output params:      n/a                          */
/*                                                  */
/* Observations:       This function is based on    */
/*                     functions described on that  */
/*                     link below:                  */
/*                     https://www.geeksforgeeks.org*/
/*                     /convert-floating-point-numbe*/
/*                     r-string                     */
/*                                                  */
/* Author:             Shubham Singh                */
/*                     Motilal Nehru National       */
/*                     Institute of Technology,     */
/*                     Allahabad - India            */
/* ************************************************ */
void float2Str(float n, char* str){
    int dec = 0;
    int nad = 2;
    int i = 0;
    while(i < nad) {
        n *= 10;
        dec++;
        i++;
    }
    int N = (int)n;
    i = 4;
    str[5] = '\0';
    while(i > -1) {
        str[i] = N%10+48;
        N /=10;
        dec--;
        i--;
        if (dec == 0) {
            str[i] = '.';
            i--;
        }
    }
    return;
}

/* ************************************************ */
/* Method name:        string2Float                 */
/* Method description: Converts a given string      */
/*                     (format:x.xx) to a float     */
/*                     number.                      */
/*                                                  */
/* Input params:       ucText -> String             */
/* Output params:      float number                 */
/* ************************************************ */
float string2Float(unsigned char *ucText)
{
	int i = 0;
	float j = 1;
	float fNumber = 0;
	while (ucText[i] != '\0')
	{
		/* case the character is '.' or ',' */
		if(ucText[i] == '.' || ucText[i] == ','){
			i++;
		}
		else {
			/* Converting based on the ASCII table*/
	   		fNumber += (ucText[i] - '0')*j;
	   		j = j / 10;
	   		i++;
		}
	}
	return fNumber;
}

/* ************************************************ */
/* Method name:        string2FloatB                */
/* Method description: Converts a given string      */
/*                     (format:xx.xx) to a float    */
/*                     number.                      */
/*                                                  */
/* Input params:       ucText -> String             */
/* Output params:      float number                 */
/* ************************************************ */
float string2FloatB(unsigned char *ucText)
{
	int i = 0;
	float j = 10;
	float fNumber = 0;
	while (ucText[i] != '\0')
	{
		/* case the character is '.' or ',' */
		if(ucText[i] == '.' || ucText[i] == ','){
			i++;
		}
		else {
			/* Converting based on the ASCII table */
	   		fNumber += (ucText[i] - '0')*j;
	   		j = j / 10;
	   		i++;
		}
	}
	return fNumber;
}

/* ************************************************ */
/* Method name:        uintToString                 */
/* Method description: Converts a given integer     */
/*                     number to a string           */
/*                     a integer number.            */
/*                                                  */
/* Input params:       ucText -> String (format:xxx)*/
/*                     uiValue -> unsigned int      */
/* Output params:      n/a                          */
/* ************************************************ */
void uintToString(char *cStr, unsigned int uiValue)
{
	if (uiValue == 0)
	{
		cStr[0] = '0';
		cStr[1] = '\0';
	} else {
		int aux;
		int i = 0;
		while (uiValue > 0)
		{
			aux = (int)uiValue%10;
			cStr[i] = aux+48;
			uiValue /= 10;
			i++;
		}
		cStr[i] = '\0';
		i--;
		char cAux;
		int j = 0;
		while (i > j) {
		    cAux = cStr[j];
		    cStr[j] = cStr[i];
		    cStr[i] = cAux;
		    j++;
		    i--;
		}
	}
}

/* ************************************************ */
/* Method name:        string2Uint                  */
/* Method description: Converts a given string to   */
/*                     a integer number.            */
/*                                                  */
/* Input params:       ucText -> String (format:xxx)*/
/* Output params:      int number                   */
/* ************************************************ */
int string2Uint(unsigned char *ucText)
{
	int i = 0;
	float j = 100;
	int iAux = 0;
	while (ucText[i] != '\0')
	{
		iAux += (ucText[i] - '0')*j;
	   j = j / 10;
	   i++;
	}
	return  iAux;
}

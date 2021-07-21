/* ***************************************************************** */
/* File name:        lcd.c                                           */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related to the LCD HARDWARE based on the KS006U */
/*                   controller                                      */
/* Author name:      dloubach                                        */
/* Creation date:    16out2015                                       */
/* Revision date:    19jun2021                                       */
/* ***************************************************************** */

#include "lcd.h"
#include "board.h"
#include "util.h"
#include "tacometro.h"
#include "aquecedorECooler.h"
#include "adc.h"
#include "pid.h"

/* system includes */
#include "fsl_clock_manager.h"

/* line and columns */
#define LINE0        0U
#define LINE1        1U
#define COLUMN0      0U
#define L0C0_BASE    0x80 /* line 0, column 0 */
#define L1C0_BASE    0xC0 /* line 1, column 0 */
#define MAX_COLUMN   15U

int iMode = 0;

/* ************************************************ */
/* Method name:        lcd_initLcd                  */
/* Method description: Initialize the LCD function  */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */
void lcd_initLcd(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= PORTC_IDX;

    /* set pin as gpio */
    PORTC_PCR0 |= 0x100;
    PORTC_PCR1 |= 0x100;
    PORTC_PCR2 |= 0x100;
    PORTC_PCR3 |= 0x100;
    PORTC_PCR4 |= 0x100;
    PORTC_PCR5 |= 0x100;
    PORTC_PCR6 |= 0x100;
    PORTC_PCR7 |= 0x100;
    PORTC_PCR8 |= 0x100;
    PORTC_PCR9 |= 0x100;

    /* set pin as digital output */
    for (int i = 0; i < 10; i++) {
        GPIOC_PDDR |= LCD_DATA_DIR << i;
    }

    // turn-on LCD, with no cursor and no blink
    lcd_sendCommand(CMD_NO_CUR_NO_BLINK);

    // init LCD
    lcd_sendCommand(CMD_INIT_LCD);

    // clear LCD
    lcd_sendCommand(CMD_CLEAR);

    // LCD with no cursor
    lcd_sendCommand(CMD_NO_CURSOR);

    // cursor shift to right
    lcd_sendCommand(CMD_CURSOR2R);
}

/* ************************************************ */
/* Method name:        lcd_write2Lcd                */
/* Method description: Send command or data to LCD  */
/* Input params:       ucBuffer => char to be send  */
/*                     cDataType=>command LCD_RS_CMD*/
/*                     or data LCD_RS_DATA          */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_write2Lcd(unsigned char ucBuffer,  unsigned char cDataType)
{
    /* writing data or command */
    if(LCD_RS_CMD == cDataType)
        /* will send a command */
        GPIOC_PDOR &= ~(1u << LCD_RS_PIN);
    else
        /* will send data */
        GPIOC_PDOR |= (1u << LCD_RS_PIN);

    /* write in the LCD bus */
    for (int i = 0; i < 8; i++) {
        if(((ucBuffer & (1u << i)) >> i) == 1U){
    	    GPIOC_PSOR = (1u << i);
        }
        else
        {
        GPIOC_PCOR = (1u << i);
        }
    }

    /* enable, delay, disable LCD */
    /* this generates a pulse in the enable pin */
    GPIOC_PDOR |= (1u << LCD_ENABLE_PIN);
    util_genDelay1ms();
    GPIOC_PDOR &= ~(1u << LCD_ENABLE_PIN);
    util_genDelay1ms();
    util_genDelay1ms();
}

/* ************************************************ */
/* Method name:        lcd_writeData                */
/* Method description: Write data to be displayed   */
/* Input params:       ucData => char to be written */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeData(unsigned char ucData)
{
    /* just a relay to send data */
    lcd_write2Lcd(ucData, LCD_RS_DATA);
}

/* ************************************************ */
/* Method name:        lcd_sendCommand              */
/* Method description: Write command to LCD         */
/* Input params:       ucCmd=>command to be executed*/
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_sendCommand(unsigned char ucCmd)
{
    /* just a relay to send command */
    lcd_write2Lcd(ucCmd, LCD_RS_CMD);
}

/* ************************************************ */
/* Method name:        lcd_setCursor                */
/* Method description: Set cursor line and column   */
/* Input params:       cLine = LINE0..LINE1         */
/*                     cColumn = COLUMN0..MAX_COLUMN*/
/* Output params:       n/a                         */
/* ************************************************ */
void lcd_setCursor(unsigned char cLine, unsigned char cColumn)
{
    char cCommand;

    if(LINE0 == cLine)
        /* line 0 */
        cCommand = L0C0_BASE;
    else
        /* line 1 */
        cCommand = L1C0_BASE;

    /* maximum MAX_COLUMN columns */
    cCommand += (cColumn & MAX_COLUMN);

    // send the command to set the cursor
    lcd_sendCommand(cCommand);
}

/* ************************************************ */
/* Method name:        lcd_writeString              */
/* Method description: Write string to be displayed */
/* Input params:       cBuffer => string to be      */
/*                     written in LCD               */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeString(const char *cBuffer)
{
    while(*cBuffer)
    {
        lcd_writeData(*cBuffer++);
    };
}

/* ************************************************ */
/* Method name:        lcd_dummyText                */
/* Method description: Write a dummy hard coded text*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_dummyText(void)
{
    // clear LCD
    lcd_sendCommand(CMD_CLEAR);

    // set the cursor line 0, column 1
    lcd_setCursor(0,1);

    // send string
    lcd_writeString("*** ES670 ***");

    // set the cursor line 1, column 0
    lcd_setCursor(1,0);
    lcd_writeString("Prj Sis Embarcad");
}

/* ************************************************ */
/* Method name:        lcd_writeText                */
/* Method description: Write a dummy hard coded text*/
/* Input params:       iLine = number 0 or 1, that  */
/*                             represents the line  */
/*                     cData = string to be written */
/*                              in LCD              */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeText(int iLine, const char *cData)
{
    switch(iLine)
    {
	    case 0:
	        lcd_setCursor(LINE0, COLUMN0);
	        break;
	    case 1:
	    	lcd_setCursor(LINE1, COLUMN0);
            break;
	    default:
		    lcd_setCursor(LINE0, COLUMN0);
		    break;
    }
    lcd_writeString(cData);
}

/* ************************************************ */
/* Method name:        lcd_writeCooler              */
/* Method description: Write the rotation of the    */
/*                     cooler on LCD                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeCooler() {
	char cStr[10];
	lcd_setCursor(LINE1,COLUMN0);
	lcd_writeString("C:");
	lcd_setCursor(LINE1,2U);
	uintToString(cStr, getCoolerSpeed());
	lcd_writeString(cStr);
	lcd_setCursor(LINE1,7U);
	lcd_writeString("dCC:");
	lcd_setCursor(LINE1,11U);
	float2Str(getCoolerDuty(), cStr);
	lcd_writeString(cStr);
}

/* ************************************************ */
/* Method name:        lcd_setIMOD                  */
/* Method description: Set the global variable iMode*/
/* Input params:       int iV = iMode value         */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_setIMOD(int iV) {
	iMode = iV;
}

/* ************************************************ */
/* Method name:        lcd_writeLCD                 */
/* Method description: write on LCD                 */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeLCD() {
	char cStr[10];
	/* Defaut Mode */
	if(iMode == 0) {
		lcd_setCursor(LINE0,COLUMN0);
		lcd_writeString("T:");
		lcd_setCursor(LINE0,2U);
		float2Str(adc_getTemperature(), cStr);
		lcd_writeString(cStr);
		lcd_setCursor(LINE0,8U);
		lcd_writeString("Tp:");
		lcd_setCursor(LINE0,11U);
		float2Str(getPresetTemp(), cStr);
		lcd_writeString(cStr);

		lcd_setCursor(LINE1,COLUMN0);
		lcd_writeString("C:");
		lcd_setCursor(LINE1,2U);
		uintToString(cStr, getCoolerSpeed());
		lcd_writeString(cStr);
	} else {
		/* K parameters Mode */
		lcd_setCursor(LINE0,COLUMN0);
		lcd_writeString("kp:");
		lcd_setCursor(LINE0,3U);
		float2Str(pid_getKp(),cStr);
		lcd_writeString(cStr);
		lcd_setCursor(LINE0,8U);
		lcd_writeString("ki:");
		lcd_setCursor(LINE0,11U);
		float2Str(pid_getKi(),cStr);
		lcd_writeString(cStr);

		lcd_setCursor(LINE1,COLUMN0);
		lcd_writeString("kd:");
		lcd_setCursor(LINE1,3U);
		float2Str(pid_getKd(),cStr);
		lcd_writeString(cStr);
	}
}

/* ************************************************ */
/* Method name:        getIMode                     */
/* Method description: returns the iMode value      */
/* Input params:       n/a                          */
/* Output params:      int iMode                    */
/* ************************************************ */
int getIMode(){
	return iMode;
}

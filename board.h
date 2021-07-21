/* ***************************************************************** */
/* File name:        board.h                                         */
/* File description: Header file containing the peripherals mapping  */
/*                     of the peripheral board for the ES670 hardware*/
/*                                                                   */
/* Author name:      Rodrigo M Bacurau                               */
/* Creation date:    26fev2020                                       */
/* Revision date:    28may2021                                       */
/* ***************************************************************** */

#ifndef SOURCES_BOARD_H_
#define SOURCES_BOARD_H_

/* system includes */
#include <MKL25Z4.h>

/* FDRMKL25Z RGB LED pins defintions */
#define RED_LED_PORT_BASE_PNT    PORTB /* peripheral port base pointer */
#define RED_LED_GPIO_BASE_PNT    PTB   /* peripheral gpio base pointer */
#define RED_LED_PIN		         (uint32_t) 18u
#define GREEN_LED_PORT_BASE_PNT  PORTB /* peripheral port base pointer */
#define GREEN_LED_GPIO_BASE_PNT  PTB   /* peripheral gpio base pointer */
#define GREEN_LED_PIN	         (uint32_t) 19u
#define BLUE_LED_PORT_BASE_PNT   PORTD /* peripheral port base pointer */
#define BLUE_LED_GPIO_BASE_PNT   PTD   /* peripheral gpio base pointer */
#define BLUE_LED_PIN	         (uint32_t) 1u

/*                 General uC definitions                 */

/* Clock gate control */
#define  CGC_CLOCK_DISABLED         0x00U
#define  CGC_CLOCK_ENABLED          0x01U

/* GPIO input / output */
#define GPIO_INPUT                  0x00U
#define GPIO_OUTPUT                 0x01U

/*                 LCD DEFINITIONS                 */
#define LCD_PORT_BASE_PNT           PORTC                                   /* peripheral port base pointer */
#define LCD_GPIO_BASE_PNT           PTC                                     /* peripheral gpio base pointer */
#define LCD_RS_PIN                  8U                                      /* register selector */
#define LCD_RS_DIR                  1U
#define LCD_RS_ALT                  1U
#define LCD_ENABLE_PIN              9U                                      /* enable pin */
#define LCD_ENABLE_DIR              1U
#define LCD_ENABLE_ALT              1U
#define LCD_RS_HIGH                 1U
#define LCD_RS_DATA                 LCD_RS_HIGH
#define LCD_RS_LOW                  0U
#define LCD_RS_CMD                  LCD_RS_LOW
#define LCD_ENABLED                 1U
#define LCD_DISABLED                0U
#define LCD_DATA_DIR                1U                                      /* LCD data pins */
#define LCD_DATA_ALT                1U
#define LCD_DATA_DB0_PIN            0u
#define LCD_DATA_DB1_PIN            1u
#define LCD_DATA_DB2_PIN            2u
#define LCD_DATA_DB3_PIN            3U
#define LCD_DATA_DB4_PIN            4U
#define LCD_DATA_DB5_PIN            5U
#define LCD_DATA_DB6_PIN            6U
#define LCD_DATA_DB7_PIN            7U
#define LCD_DATA_DB0_DIR            (GPIO_OUTPUT << LCD_DATA_DB0_PIN)
#define LCD_DATA_DB1_DIR            (GPIO_OUTPUT << LCD_DATA_DB1_PIN)
#define LCD_DATA_DB2_DIR            (GPIO_OUTPUT << LCD_DATA_DB2_PIN)
#define LCD_DATA_DB3_DIR            (GPIO_OUTPUT << LCD_DATA_DB3_PIN)
#define LCD_DATA_DB4_DIR            (GPIO_OUTPUT << LCD_DATA_DB4_PIN)
#define LCD_DATA_DB5_DIR            (GPIO_OUTPUT << LCD_DATA_DB5_PIN)
#define LCD_DATA_DB6_DIR            (GPIO_OUTPUT << LCD_DATA_DB6_PIN)
#define LCD_DATA_DB7_DIR            (GPIO_OUTPUT << LCD_DATA_DB7_PIN)
/*                 END OF LCD DEFINITIONS                 */

/* PORTS DEFINITIONS */
#define PORT_A 0x200;
#define PORT_B 0x400;
#define PORT_C 0x800;
#define PORT_D 0x1000;
#define PORT_E 0x2000;
/* END OF PORTS DEFINITIONS */

/* DISPLAY 7SEG DEFINITIONS */
#define SET_AS_GPIO    0X100

#define CHAR_0        0x0000003F
#define CHAR_1        0x00000006
#define CHAR_2        0x0000005B
#define CHAR_3        0x0000004F
#define CHAR_4        0x00000066
#define CHAR_5        0x0000006D
#define CHAR_6        0x0000007D
#define CHAR_7        0x00000007
#define CHAR_8        0x0000007F
#define CHAR_9        0x0000006F
#define CHAR_0p       0x000000BF
#define CHAR_1p       0x00000086
#define CHAR_2p       0x000000DB
#define CHAR_3p       0x000000CF
#define CHAR_4p       0x000000E6
#define CHAR_5p       0x000000ED
#define CHAR_6p       0x000000FD
#define CHAR_7p       0x00000087
#define CHAR_8p       0x000000FF
#define CHAR_9p       0x000000EF
#define CHAR_Vp       0x00000080
#define CHAR_ALL      0x000000FF
#define CHAR_ERASE    0xFFFFFF00

#define DISP_1        13
#define DISP_2        12
#define DISP_3        11
#define DISP_4        10
/* END OF DISPLAY 7SEG DEFINITIONS */


/* COOLER PORT and PIN */
#define PORT_COOLER		9u /*PORTA*/
#define PIN_COOLER		13U

/* HEATER PORT and PIN */
#define PORT_HEATER		9u /*PORTA*/
#define PIN_HEATER		12U

/* Registers pins */
#define PIN0	0U
#define PIN1	1U
#define PIN2	2U
#define PIN3	3U
#define PIN4	4U
#define PIN5	5U
#define PIN6	6U
#define PIN7	7U
#define PIN8	8U
#define PIN9	9U
#define PIN10	10U
#define PIN11	11U
#define PIN12	12U
#define PIN13	13U
#define PIN14	14U
#define PIN15	15U
#define PIN16	16U
#define PIN17	17U
#define PIN18	18U
#define PIN19	19U
#define PIN20	20U
#define PIN21	21U
#define PIN22	22U
#define PIN23	23U
#define PIN24	24U
#define PIN25	25U
#define PIN26	26U
#define PIN27	27U
#define PIN28	28U
#define PIN29	29U
#define PIN30	30U
#define PIN31	31U

/* TPM DEFINITIONS */
#define CLK_TPM0	0x01000000        /* the bit at SIM_SCGC6 register that enables clock to the TPM0 module.*/
#define CLK_TPM1	0x02000000        /* the bit at SIM_SCGC6 register that enables clock to the TPM0 module.*/
#define CLK_TPM2	0x04000000         /* the bit at SIM_SCGC6 register that enables clock to the TPM0 module.*/

#define PRESCALE_DIV1		0  /* pin 0 of TPMx_SC register.*/
#define PRESCALE_DIV2		1  /* pin 1 of TPMx_SC register.*/
#define PRESCALE_DIV4		2  /* pin 2 of TPMx_SC register.*/
#define PRESCALE_DIV8		3  /* pin 3 of TPMx_SC register.*/
#define PRESCALE_DIV16		4  /* pin 4 of TPMx_SC register.*/
#define PRESCALE_DIV32		5  /* pin 5 of TPMx_SC register.*/
#define PRESCALE_DIV64		6  /* pin 6 of TPMx_SC register.*/
#define PRESCALE_DIV128		7  /* pin 7 of TPMx_SC register.*/

#define MAX_COUNT	0xFFFE
#define IMAX_COUNT	65534
/* END OF TPM DEFINITIONS */

/* PMW DEFINITIONS */
#define MUX_PGIO	0x100		/* MUX = 001*/
#define MUX_PWM		0x300		/* MUX = 011*/
/* END OF PMW DEFINITIONS */

/* TEMPERATURE SENSOR DIODE DEFINITIONS */
#define  THERMOMETER_PORT_BASE_PNT  PORTE                         /* peripheral port base pointer */
#define  THERMOMETER_GPIO_BASE_PNT  PTE                           /* peripheral gpio base pointer */
#define  THERMOMETER_PIN            21U                           /* thermometer pin */
#define  THERMOMETER_DIR            (GPIO_INPUT << TERMOMETER_PIN)
#define  THERMOMETER_ALT            0x00u
/* END OF TEMPERATURE SENSOR DIODE DEFINITIONS */

#endif /* SOURCES_BOARD_H_ */

/* ***************************************************************** */
/* File name:        util.h                                          */
/* File description: Header file containing the function/methods     */
/*                   prototypes of util.c                            */
/*                   Those delays were tested under the following:   */
/*                   core clock @ 40MHz                              */
/*                   bus clock @ 20MHz                               */
/* Author name:      dloubach                                        */
/* Creation date:    09jan2015                                       */
/* Revision date:    19jun2021                                       */
/* ***************************************************************** */

#ifndef UTIL_H
#define UTIL_H

/* ************************************************ */
/* Method name:        util_genDelay088us           */
/* Method description: generates ~ 088 micro sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay088us(void);


/* ************************************************ */
/* Method name:        util_genDelay250us           */
/* Method description: generates ~   250 micro sec  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay250us(void);


/* ************************************************ */
/* Method name:        util_genDelay1ms             */
/* Method description: generates ~   1 mili sec     */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay1ms(void);


/* ************************************************ */
/* Method name:        util_genDelay10ms            */
/* Method description: generates ~   10 mili sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay10ms(void);

/* ************************************************ */
/* Method name:        util_genDelay10ms            */
/* Method description: generates ~   100 mili sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay100ms(void);

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
void float2Str(float n, char* str);

/* ************************************************ */
/* Method name:        string2Float                 */
/* Method description: Converts a given string      */
/*                     (format:x.xx) to a float     */
/*                     number.                      */
/*                                                  */
/* Input params:       ucText -> String             */
/* Output params:      float number                 */
/* ************************************************ */
float string2Float(unsigned char *ucText);

/* ************************************************ */
/* Method name:        string2FloatB                */
/* Method description: Converts a given string      */
/*                     (format:xx.xx) to a float    */
/*                     number.                      */
/*                                                  */
/* Input params:       ucText -> String             */
/* Output params:      float number                 */
/* ************************************************ */
float string2FloatB(unsigned char *ucText);

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
void uintToString(char *cStr, unsigned int uiValue);

/* ************************************************ */
/* Method name:        string2Uint                  */
/* Method description: Converts a given string to   */
/*                     a integer number.            */
/*                                                  */
/* Input params:       ucText -> String (format:xxx)*/
/* Output params:      int number                   */
/* ************************************************ */
int string2Uint(unsigned char *ucText);

#endif /* UTIL_H */

/* ***************************************************************** */
/* File name:        aquecedorECooler.h                              */
/* File description: Header file containing the prototypes of the    */
/*                   functions used to configure and set the cooler  */
/*                   fan and the heater                              */
/*                                                                   */
/* Author name:      Leonardo Vinicius de Souza                      */
/*                   Wallace da Cruz Pereira                         */
/* Creation date:    27apr2021                                       */
/* Revision date:                                                    */
/* ***************************************************************** */

#ifndef AQUECEDORECOOLER_H
#define AQUECEDORECOOLER_H

/* ************************************************ */
/* Method name:        PWM_init                     */
/* Method description: Configure the channels 0 and */
/*                     1 of the TPM1 as EdgeAligned */
/*                     PWM, setting the frequency   */
/*                     between 5 and 20Hz.          */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void PWM_init(void);

/* ************************************************ */
/* Method name:        heater_init                  */
/* Method description: Set the signal PWM on the    */
/*                     pins PTA12.                  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void heater_init(void);

/* ************************************************ */
/* Method name:        coolerfan_init               */
/* Method description: Set the signal PWM on the    */
/*                     pins PTA13.                  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void coolerfan_init(void);

/* ************************************************ */
/* Method name:        util_genDelay1ms             */
/* Method description: Configure the duty cycle of  */
/*                     the signal PWM.              */
/* Input params:       float fHeaterDuty            */
/* Output params:      n/a                          */
/* ************************************************ */
void heater_PWMDuty();

/* ************************************************ */
/* Method name:        coolerfan_PWMDuty            */
/* Method description: Configure the duty cycle of  */
/*                     the signal PWM.              */
/* Input params:       float fCoolerDuty            */
/* Output params:      n/a                          */
/* ************************************************ */
void coolerfan_PWMDuty();

/* ************************************************ */
/* Method name:        roundNumber                  */
/* Method description: Round a number from float    */
/*                     type to integer type.        */
/* Input params:       float fNumber                */
/* Output params:      integer                      */
/* ************************************************ */
int roundNumber(float fNumber);

/* ************************************************ */
/* Method name:        getHeaterDuty                */
/* Method description: Return the value of Dutty    */
/*                     cycle of the Heater.         */
/* Input params:       n/a                          */
/* Output params:      float fNumber                */
/* ************************************************ */
float getHeaterDuty(void);

/* ************************************************ */
/* Method name:        getCoolerDuty                */
/* Method description: Return the value of Dutty    */
/*                     cycle of the Cooler.         */
/* Input params:       n/a                          */
/* Output params:      float fNumber                */
/* ************************************************ */
float getCoolerDuty(void);

/* ************************************************ */
/* Method name:        setCooler                    */
/* Method description: Configure the global variable*/
/*                     duty cycle of the cooler     */
/* Input params:       float fCoolerDuty            */
/* Output params:      n/a                          */
/* ************************************************ */
void setCooler(float fCoolerDuty);

/* ************************************************ */
/* Method name:        setHeater                    */
/* Method description: Configure the global variable*/
/*                     duty cycle of the heater     */
/* Input params:       float fHeaterDuty            */
/* Output params:      n/a                          */
/* ************************************************ */
void setHeater(float fHeaterDuty);

/* ************************************************ */
/* Method name:        getPresetTemp                */
/* Method description: Return the value of preset   */
/*                     of the temperature.          */
/* Input params:       n/a                          */
/* Output params:      float fNumber                */
/* ************************************************ */
float getPresetTemp(void);

/* ************************************************ */
/* Method name:        setPresetTemp                */
/* Method description: Configure the global variable*/
/*                     preset of the temperature    */
/* Input params:       float fPreSet                */
/* Output params:      n/a                          */
/* ************************************************ */
void setPresetTemp(float fPreSet);

#endif /* AQUECEDORECOOLER_H */

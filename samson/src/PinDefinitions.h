/*
 * PinDefinitions.h
 *
 * Created: 09/12/2023
 * Author: scott.sullivan
 */


#ifndef PINDEFINITIONS_H_
#define PINDEFINITIONS_H_
#include "sam.h"

/****************PIN DEFINITIONS******************/
/***** BOARD - AT-SAM-DA1G */

#define I2C_GROUP 0
#define I2C_SDA_PIN PIN_PA08 
#define I2C_SCL_PIN PIN_PA09 
#define I2C_SERCOM SERCOM0

#define I2C_MOTOR_ADDRESS 0x00 // Motor Controller M1T550 Gen.Address
#define I2C_SLAVE_ADDRESS 0x10 // Motron Default Address (d16)

#define TIMEOUT 1000



/****************I2C SLAVES**********************/
#define MOTORON_I2C_ADDRESS 0x10  // This is the 7-bit I2C address for Motoron.



//**************USB**************************/
#define USB_N PORT_PA24
#define USB_P PORT_PA25



/**************LED INDICATORS********************/
#define PORTA (0ul)
#define PORTB (1ul)

#define STATUS_LED_GROUP 0
#define STATUS_LED_PORT PORTA
#define STATUS_LED_PIN PIN_PA17
#define STATUS_LED_MASK PORT_PA17




#endif /* PINDEFINITIONS_H_ */
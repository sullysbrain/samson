/*
 * I2CMaster.h
 *
 * Created: 09/21/2023
 * Author: scott.sullivan
 */ 


#include "sam.h"

#ifndef I2CCONTROLLER_H_
#define I2CCONTROLLER_H_

void I2CControllerInit();
bool I2CDataTransmit(uint8_t *data, int data_size, Sercom* sercom_number);


#endif /* I2CMASTER_H_ */
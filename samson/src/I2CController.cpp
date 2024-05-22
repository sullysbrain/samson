/*
 * I2CMaster.cpp
 *
 * Created: 09/21/2023
 * Author: scott.sullivan
 */ 


#include "I2CController.h"
#include "sam.h"
#include "PinDefinitions.h"


void I2CControllerInit(){
	REG_SERCOM0_I2CM_STATUS;
	
	//Set the pins as outputs and set up the PMux to SERCOM (Function 'C')
	//PORT->Group[I2C_GROUP].DIRCLR.reg = C1_SDA|C1_SCL|C2_SDA|C2_SCL|C3_SDA|C3_SCL|C4_SDA|C4_SCL;
	
	// Set up the pin muxing to connect the pins to the SERCOM peripheral
	PORT->Group[I2C_GROUP].PINCFG[I2C_SDA_PIN].bit.PMUXEN = 1;
	PORT->Group[I2C_GROUP].PINCFG[I2C_SCL_PIN].bit.PMUXEN = 1;

	PORT->Group[0].PMUX[I2C_SDA_PIN / 2].bit.PMUXE = PORT_PMUX_PMUXE_C_Val; // Set PA12 to function C
	PORT->Group[0].PMUX[I2C_SCL_PIN / 2].bit.PMUXO = PORT_PMUX_PMUXO_C_Val; // Set PA13

	// NEED TO SET UP GCLK
	// Enable the I2C_SERCOM clock
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0|PM_APBCMASK_SERCOM1|PM_APBCMASK_SERCOM2|PM_APBCMASK_SERCOM3;
	while(I2C_SERCOM->I2CM.SYNCBUSY.bit.SYSOP);


	// I2C_SERCOM
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_GEN(0) | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID(SERCOM0_GCLK_ID_CORE);
	//GCLK->CLKCTRL.reg = GCLK_CLKCTRL_GEN(0) | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID(SERCOM0_GCLK_ID_SLOW);
	//	SERCOM1
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_GEN(0)|GCLK_CLKCTRL_CLKEN|GCLK_CLKCTRL_ID(SERCOM1_GCLK_ID_CORE);
	//GCLK->CLKCTRL.reg = GCLK_CLKCTRL_GEN(0)|GCLK_CLKCTRL_CLKEN|GCLK_CLKCTRL_ID(SERCOM1_GCLK_ID_SLOW);
	//	SERCOM2
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_GEN(0)|GCLK_CLKCTRL_CLKEN|GCLK_CLKCTRL_ID(SERCOM2_GCLK_ID_CORE);
	//GCLK->CLKCTRL.reg = GCLK_CLKCTRL_GEN(0)|GCLK_CLKCTRL_CLKEN|GCLK_CLKCTRL_ID(SERCOM1_GCLK_ID_SLOW);

	// 1. Select I2C Master (0x4) mode
	I2C_SERCOM->I2CM.CTRLA.reg |= SERCOM_I2CM_CTRLA_MODE_I2C_MASTER;

	// Set the bus speed for I2C_SERCOM to the standard 100kHz
	I2C_SERCOM->I2CM.CTRLA.reg |= SERCOM_I2CM_CTRLA_SPEED(0);
	I2C_SERCOM->I2CM.CTRLA.bit.RUNSTDBY = 1;

	// 2. If desired, select the SDA Hold Time value
	I2C_SERCOM->I2CM.CTRLA.reg |= SERCOM_I2CM_CTRLA_SDAHOLD(3);


	// 3. If desired, enable smart operation
	I2C_SERCOM->I2CM.CTRLB.bit.SMEN = 1;
	while(I2C_SERCOM->I2CM.SYNCBUSY.reg);

	// 5. In Master mode:
	// 5.1. Select the inactive bus time-out (if needed)
	// I2C_SERCOM->I2CM.CTRLA.bit.INACTOUT = 0;
	// 5.2. Write the Baud Rate register (BAUD) to generate the desired baud rate
	I2C_SERCOM->I2CM.BAUD.reg |= SERCOM_I2CM_BAUD_BAUD(48);
	I2C_SERCOM->I2CM.BAUD.reg |= SERCOM_I2CM_BAUD_HSBAUD(13);
	while(I2C_SERCOM->I2CM.SYNCBUSY.reg);

	// Enable the interrupts
	I2C_SERCOM->I2CM.INTENSET.bit.MB = 1;
	I2C_SERCOM->I2CM.INTENSET.bit.SB = 1;

	// Enable the I2C_SERCOM Module
	I2C_SERCOM->I2CM.CTRLA.bit.ENABLE = 1;
	while(I2C_SERCOM->I2CM.SYNCBUSY.reg);
	I2C_SERCOM->I2CM.STATUS.reg |= SERCOM_I2CM_STATUS_BUSSTATE(1);
	while(I2C_SERCOM->I2CM.SYNCBUSY.reg);

	
}


bool I2CDataTransmit(uint8_t *data, int data_size, Sercom* sercom_number){
	
	/////// SET SLAVE ADDRESS //////
	/* The slave address is shifted left by one bit because the least significant bit of the address is used to indicate the read/write direction of the transaction. A value of 0 indicates a write operation, while a value of 1 indicates a read operation.

	Since the ADDR register expects a 7-bit address, the least significant bit is not included in the address value. Therefore, the slave address is shifted left by one bit to make room for the read/write bit.
	*/

	// Orion Box MASTER: Sets Slave Address:
	//sercom_number->I2CM.ADDR.reg = 0b0100010;
	// From Orion SLAVE:
	// SERCOM0->I2CS.ADDR.reg = SERCOM_I2CS_ADDR_ADDR(0b0010001);

	uint8_t slaveAddress = MOTORON_I2C_ADDRESS;	
	sercom_number->I2CM.ADDR.reg = slaveAddress << 1;  	
	
	while(sercom_number->I2CM.INTFLAG.bit.MB == 0);
	
	// This line was commented out by Tyler
	//while(0==(SERCOM1->I2CM.INTFLAG.reg & SERCOM_I2CM_INTFLAG_MB));
	if(sercom_number->I2CM.STATUS.reg & SERCOM_I2CM_STATUS_RXNACK){
		sercom_number->I2CM.CTRLB.reg |= SERCOM_I2CM_CTRLB_CMD(3);
		return false;
	}
	for(int i = 0; i < data_size; i++){
		sercom_number->I2CM.DATA.reg = data[i];
		while(0==(sercom_number->I2CM.INTFLAG.reg & SERCOM_I2CM_INTFLAG_MB));
		if(sercom_number->I2CM.STATUS.reg & SERCOM_I2CM_STATUS_RXNACK){
			sercom_number->I2CM.CTRLB.reg |= SERCOM_I2CM_CTRLB_CMD(3);
			return false;
		}
	}
	sercom_number->I2CM.CTRLB.reg |= SERCOM_I2CM_CTRLB_CMD(3);
	return true;
}
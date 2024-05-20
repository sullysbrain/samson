 /*
 * SAMD21 J Breakout Board
 *
 * Created: 9/12/2023
 * Author : scott.sullivan
 */ 


#include "sam.h"
#include "PinDefinitions.h"
#include "I2CController.h"


int main(void)
{
    /* Initialize the SAM system */
	//MaxClockSpeed();
    SystemInit();
	
	// using raw c++, turn on the STATUS LED

	// Set the STATUS LED pin as an output
	REG_PORT_DIR0 = STATUS_LED_MASK;
	REG_PORT_OUTSET0 = STATUS_LED_MASK;

	
		
	while(true){


	}
}


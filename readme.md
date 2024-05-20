# SAMD21 Breakout Board

## SS Breakout Board
Tutorial for sending I2C data from the ARM based MCU, the AT-SAMD21-G18A-F, from Microchip (aka Atmel). 

## TODO
PWM signal based on input values, send as uint16_t value for duty cycle.



## Troubleshooting
### In case of "No device found on cu.usbmodem####" error
This issue has been most noticeable on Macs. After resetting the board into the bootloader, the delay before attempting an upload isn't long enough. After the first upload try, you should see the yellow "RX" LED illuminate – usually indicating the board has reset into bootloader mode. Another upload try should take.

Until solved, you may have to deal with either double-upload-clicking, or resetting the board into bootloader before uploading.


### IF NOT FOUND IN USB DEVICE:
Double tap reset button, resets bootloader


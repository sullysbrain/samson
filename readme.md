# Project SAMSON

## Raspberry Pi Board
This will be the brains of the Neural Net. I wil be running computer vision and llm models on the Pi. Current plan is to upgrade and use the Pi 5 with 8GB of RAM. Testing and dev is currently being done on a Pi 4 B, 4GB model. 
	- CURRENT: Pi 4 Model B |4 GB | 1.8 GHz quad-core Cortex-A72 (ARM v8) 64-bit
	- future: Pi 5 | 8GB | 2.4GHz quad-core 64-bit Arm Cortex-A76 CPU

## SAMD Breakout Board
This board will be the 'nervous system' and control any and all actuators for SAMSON. Due to my own familiarity of the SAMD architecture, I will be using the SAMD21. Specifically, I am using the ATSAMD21G18A ( ATSAMD mini breakout board).
	- V1:  ATSAMD21G18 32-bit/48MHz ARM Cortex-M0+
	- 256KB Flash Memory, 32KB SRAM, 32KB of EEPROM (emulated in Flash)


## TODO
- PWM signal based on input values, send as uint16_t value for duty cycle.
- motor controller for mobility
- Use  Mecanum Wheels for omnnidirection movement

## Troubleshooting

### SAMD21 loading:
In case of "No device found on cu.usbmodem####" error
This issue has been most noticeable on Macs. After resetting the board into the bootloader, the delay before attempting an upload isn't long enough. After the first upload try, you should see the yellow "RX" LED illuminate – usually indicating the board has reset into bootloader mode. Another upload try should take.

Until solved, you may have to deal with either double-upload-clicking, or resetting the board into bootloader before uploading.


### IF NOT FOUND IN USB DEVICE:
Double tap reset button, resets bootloader


## Raspberry Pi Notes
I will be running the brains of the SAMSON project with the Raspberry Pi, and the controller software for actuators with the SAMD. In order to make development on the Pi easier, I am installing Raspberry Pi OS for now, and installing Docker. Belo are the steps to installing Docker via SSH:
- Connect to Pi via ssh
- Upgrade all exisiting packages
	- sudo apt update
	- sudo apt upgrade
- Install Docker (security warning don't do this for general installs, only for this docker install)
	- curl -sSL https://get.docker.com | sh
- Add user to Docker group then logout for changes to take effect
	- sudo usermod -aG docker $USER
	- logout
- Verify (docker should be listed as a group that the user is in)
	- groups




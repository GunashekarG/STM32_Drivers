Registers that are used for developing driver for GPIO:

GPIO port mode regisrer
GPIO PORT OUTPUT TYPE register
GPIO port pull up pull down register
GPIO port input data register
GPIO port output data register
GPIO port bit set reset register 
GPIO alternate function low register
GPIO alternate function high register

In STM32F4XX the  GPIO ports are connected to ARM CORTEX M4 via AHB1 bus

GPIO A-GPIO E 5 ports and 80 pins are available

GPIO Mode register: configure mode of a GPIO(input/output/analog)
	It's 32 bit reg to configure 16  GPIO pins
	GPIOA_MODER - GPIOE_MODER
		4 different modes: Input, output, alternate fn, analog.
	 alternate fn: ex: UART, SPI, I2C etc..
	analog: we can apply analog voltages 
	Every 2 nits are used to set mode for every single pins since there are 4 modes

00: input
01: output
10: alternate function
11: analog

GPIO Port output type reg: when mode is output mode this is used
used to set output type (32 bits)
1: push pull output 
2: open drain output type
only 16 bits are used to set output type since only 2 type available, the later 16 bits are unused

GPIO port output speed reg:
Why?
ans: to save power
4 diff type speed
00: low speed
01: medium speed
10: high speed
11: very high speed

Low speed saves power but will have high rise and fall times - not suitable in some apps

GPIO pull up pull down reg: PUPDR REG
To configure Used to  internal pull up/ pull dow reg
00: no pull up, pull down
01: pull up
10: pull down 
11: reserved
	32 bits are used to set pull up/pull down reg of 16 GPIO ports

GPIO Port input data register: Read only
Each bit represents input (0 means grounded, 1 means +vdd) reading this gives the voltage levels of each GPIO pins

GPIO port output data register :32 bit read only register
Each bit used to write output levels to drive ground or +vdd (0 0r 1)

GPIO Alternate function register: configuring alternate function
Alternate fn low reg
Alternate fn high reg

each on supports 16 different alternate functionalities
4  its are needed for each GPIO pin

low : pin 0-7
high: pin 8-15

alternate fn ex: timer, spi, i2c etc..


LED connections: onchip
LED4: Green: PD12
LED3: Orange: PD13
LED5: Red: PD14
LED6: Blue: PD15 

0000: af0
0001: af1
0010: af2
.
.
1111: af15


Getting started: 
API Requirements: 
1: GPIO Initialization
2: Enable/ Disable GPIO port clock
3: Read from GPIO pin
4: Write to GPIO pin
5: Configure ajternate functionality
6: Interrupt handling
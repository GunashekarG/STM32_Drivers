/*
    * main.h is the header file for the 
    * application file in order to test 
    * the GPIO driver developed
*/

#ifndef __MAIN_H
#define __MAIN_H

#include "GPIO_Driver.h"

//IRQ Number macro for button
#define IRQ_NUMBER              6

//Macro for GPIO button
#define GPIO_BUTTON_PIN         0
#define GPIO_BUTTON_PORT        GPIOA

#define GPIOD_PIN_12            12
#define GPIOD_PIN_13            13
#define GPIOD_PIN_14            14
#define GPIOD_PIN_15            15

#define LED_GREEN               GPIOD_PIN_12
#define LED_ORANGE              GPIOD_PIN_13
#define LED_RED                 GPIOD_PIN_14
#define LED_BLUE                GPIOD_PIN_15

//Public functions 
void led_init(void);
void led_turn_on(GPIO_TypeDef *GPIOx, uint16_t pin);
void led_turn_off(GPIO_TypeDef *GPIOx, uint16_t pin);
void led_toggle(GPIO_TypeDef *GPIOx, uint16_t pin);

#endif
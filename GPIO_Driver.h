// This is a GPIO driver header file driver.h

/* Created by Guna shekar G
source file for GPIO driver */

#ifndef GPIO_Driver_H
#define GPIO_DRIVER_H

//Macros used for GPIO PIN initializations
#define GPIO_PIN_INPUT_MODE              ((uint32_t) 0x00)
#define GPIO_PIN_OUTPUT_MODE             ((uint32_t) 0x01)
#define GPIO_PIN_ALT_FN_MODE             ((uint32_t) 0x02)

//GPIO output type selection values 
#define GPIO_PIN_OP_TYPE_PUSHPULL           ((uint32_t) 0x00) 
#define GPIO_PIN_OP_TYPE_OPENDRAIN          ((uint32_t) 0x01) 

//GPIO speed type selection value

#define GPIO_PIN_SPEED_LOW                  ((uint32_t) 0x00)
#define GPIO_PIN_SPEED_MEDIUM               ((uint32_t) 0x01)  
#define GPIO_PIN_SPEED_HIGH                 ((uint32_t) 0x02)
#define GPIO_PIN_SPEED_VERY_HIGH            ((uint32_t) 0x03)

//GPIO pull up/pull down selection reg
#define GPIO_PIN_NO_PULL_PUSH               ((uint32_t)0x00)
#define GPIO_PIN_NO_PULL_UP                 ((uint32_t)0x01)
#define GPIO_PIN_NO_PULL_DOWN               ((uint32_t)0x02)

//Macros to enable clock for different GPIO ports in RCC register

#define _RCC_GPIOA_CLK_ENABLE()          (RCC->AHB1ENR |= (1<<0))
#define _RCC_GPIOb_CLK_ENABLE()          (RCC->AHB1ENR |= (1<<1))
#define _RCC_GPIOC_CLK_ENABLE()          (RCC->AHB1ENR |= (1<<2))
#define _RCC_GPIOD_CLK_ENABLE()          (RCC->AHB1ENR |= (1<<3))
#define _RCC_GPIOE_CLK_ENABLE()          (RCC->AHB1ENR |= (1<<4))
#define _RCC_GPIOF_CLK_ENABLE()          (RCC->AHB1ENR |= (1<<5))
#define _RCC_GPIOG_CLK_ENABLE()          (RCC->AHB1ENR |= (1<<6))
#define _RCC_GPIOH_CLK_ENABLE()          (RCC->AHB1ENR |= (1<<7))

// redefining GPIO port address
#define GPIO_PORT_A GPIOA
#define GPIO_PORT_B GPIOB
#define GPIO_PORT_C GPIOC
#define GPIO_PORT_D GPIOD
#define GPIO_PORT_E GPIOE
#define GPIO_PORT_F GPIOF
#define GPIO_PORT_G GPIOG
#define GPIO_PORT_H GPIOH
#define GPIO_PORT_I GPIOI

//Interrupt edge selection enum

typedef enum{
    INT_RISING_EDGE,
    INT_FALLING_EDGE,
    INT_RISING_FALLING_EDGE
}int_edge_sel_t;

// Data structure for GPIO initialization

typedef struct{
    unit32_t pin;       //specifies GPIO pins to be configured
    uint32_t mode;      //specifies operating mode of the selected pins
    uint32_t op_type;   // specifies output type for the selected pins
    uint32_t pull;      //specifies pull up or pull down activation of the selected pins
    uint32_t speed;     //specifies the speed for the selected pins
    uint32_t alternate; //specifies alternate function for the selected GPIO pins
}gpio_pin_conf_t;

//GPIO port address structure

typedef struct{
    __IO_uint32_t MODER;
    __IO_uint32_t OTYPER;
    __IO_uint32_t OSPEEDR;
    __IO_uint32_t PUPDR;
    __IO_uint32_t IDR;
    __IO_uint32_t ODR;
    __IO_uint32_t BSRR;
    __IO_uint32_t LCKR;
    __IO_uint32_t AFR[2];
} GPIO_Typedef;

//Driver exposed API's

/*  @brief initializes the GPIO pin
    @param *GPIOx: GPIO Port base address
    @param *gpio_pin_conf: pointer to pin conf structure by application
    @retval: none*/
void GPIO_Init(GPIO_Typedef *GPIOx, gpio_pin_conf_t *gpio_pin_conf);

/* @brief Read value from a particular pin
   @param *GPIOx: GPIO Port base address
   @param pin_no: GPIO pin number
   @retval Returns integer value(pin value) */

uint8_t GPIO_read_from_pin(GPIO_Typedef *GPIOx, uint16_t pin_no);

/* @brief Write value to GPIO pin
   @param *GPIOx: GPIO Port base address
   @param pin_no: GPIO pin number
   @param val: value to be written to the selected pin
   @retval: none
*/
void GPIO_write_to_pin(GPIO_Typedef *GPIOx, uint16_t pin_no, uint8_t val);

/* @brief sets the alternate function for the selected GPIO pin
   @param *GPIOx: GPIO Port base address
   @param pin_no: GPIO pin number
   @param alt_fn_value: alternate function to be configuured with
   @retval: none
*/
void GPIO_set_alt_function(GPIO_Typedef *GPIOx, uint16_t pin_no,uint16_t alt_fun_value);

//adding interrupt capablities for the GPIO

/*
    * @brief Configures interrupt for a given pin number
    * @param pin_no: GPIO pin number
    * @param edge_sel: Slect the edge selection value
    * @retval none
*/
void GPIO_configure_interrupt(uint16_t pin_no, int_edge_sel_t edge_sel);

/*
    * @brief enables interrupt for a given pin number
    * @param pin_no: GPIO pin number
    * @param irq_bo: irq_number to be enabled in NVIC 
    * @retval none
*/
void GPIO_enable_interrupt(uint16_t pin_no, IRQn_Type irq_no);

/*
    * @brief clears interrupt for a given pin number
    * @param pin_no: GPIO pin number
    * @retval none
*/
void GPIO_clear_interrupt(uint16_t pin_no);

#endif
// This is a GPIO driver source file driver.c
/* Created by Guna shekar G
source file for GPIO driver */

//#include "stm32f407xx.h"
//#include <stdio.h>

/*
 *@brief Configures the mode of a pin: input, output, alt or analog mode
 *@param *GPIOx: GPIO Port Base address
 *@param pin_no: GPIO pin number
 *@param mode: mode to be configured
 @retval None
*/
static void gpio_config_pin_mode(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t mode){
    GPIOx->MODER |= (mode << ( 2 * pin_no));
}

/*
    * @brief Configure the output type of a pin
    * @param *GPIOx: GPIO Port Base address
    * @param pin_no: GPIO pin number
    * @param op_type: output type to be configured with
    * @retval None
*/
static void gpio_configure_pin_otype(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t op_type){
GPIOx->OTYPER |= (op_type<<pin_no);
}

/*
    *@brief Configures the speed of a pin
    *@param *GPIOx: GPIO Port Base address
    *@param pin_no: GPIO pin number
    *@param speed: value of the speed
    *@retval None
*/
static void gpio_configure_pin_speed(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t speed){
GPIOx->OSPEEDR |= (speed << (2* pin_no));
}

/*  @brief initializes the GPIO pin
    @param *GPIOx: GPIO Port base address
    @param *gpio_pin_conf: pointer to pin conf structure by application
    @retval: none*/
void GPIO_Init(GPIO_Typedef *GPIOx, gpio_pin_conf_t *gpio_pin_conf){

}

/*
    * @brief Activates the internall pull up or pull down resistirs
    * @param *GPIOx: GPIO Port Base address
    * @param pin_no: GPIO pin  number
    * @param pupd: specifies which resistor to activate
    * @retval None
*/
static void gpio_configure_pin_pupd(GPIO_Typedef *GPIOx, uint16_t pin_no, uint32_t pupd){
    GPIOx->PUPDR |= (pupd << (2* pin_no));
}

/* @brief Read value from a particular pin
   @param *GPIOx: GPIO Port base address
   @param pin_no: GPIO pin number
   @retval Returns integer value(pin value) */
uint8_t GPIO_read_from_pin(GPIO_Typedef *GPIOx, uint16_t pin_no){
    uint8_t value;
    value = ((GPIOx->IDR >> pin_no) & 0x00000001);
return value;
}

/* @brief Write value to GPIO pin
   @param *GPIOx: GPIO Port base address
   @param pin_no: GPIO pin number
   @param val: value to be written to the selected pin
   @retval: none
*/
void GPIO_write_to_pin(GPIO_Typedef *GPIOx, uint16_t pin_no, uint8_t val){
    if(val){
        GPIOx->ODR |= (1 << pin_no);
    }else{
        GPIOx->ODR |= ~(1 << pin_no);
    }
}


/* @brief sets the alternate function for the selected GPIO pin
   @param *GPIOx: GPIO Port base address
   @param pin_no: GPIO pin number
   @param alt_fn_value: alternate function to be configuured with
   @retval: none
*/
void GPIO_set_alt_function(GPIO_Typedef *GPIOx, uint16_t pin_no,uint16_t alt_fun_value){
    if(pin_no <= 7){
        GPIOx->AFR[0] |= (alt_fun_value << (pin_no) * 4);
    }else{
        GPIOx->AFR[1] |= (alt_fun_value << (pin_no) * 4);
    }
}

/*
    * @brief Configures interrupt for a given pin number
    * @param pin_no: GPIO pin number
    * @param edge_sel: Slect the edge selection value
    * @retval none
*/
void GPIO_configure_interrupt(uint16_t pin_no, int_edge_sel_t edge_sel){
    if(edge_sel == INT_RISING_EDGE){
        EXTI->RTSR |= 1<<pin_no;
    }else if(edge_sel == INT_FALLING_EDGE){
        EXTI->FTSR |= 1<<pin_no;
    }else if(edge_sel == INT_RISING_FALLING_EDGE){
        EXTI->RTSR |= 1<<pin_no;
        EXTI->FTSR |= 1<<pin_no;
    }else{
        //TODO
    }
}

/*
    * @brief enables interrupt for a given pin number
    * @param pin_no: GPIO pin number
    * @param irq_bo: irq_number to be enabled in NVIC 
    * @retval none
*/
void GPIO_enable_interrupt(uint16_t pin_no, IRQn_Type irq_no){
    EXTI->IMR |= 1 << pin_no;   /*Enables the interrupt using interrupt mask register---
                                *[Since GPIO doesn't have it's own dedicated IRQ line to NVIC, it has to--
                                  Go through EXTI block and this statement is must for setting--
                                  interrupt at the EXTI block]
                                */ 
    NVIC_EnableIRQ(irq_no );    //Enables the interrupt at NVIC Side
}

/*
    * @brief clears interrupt for a given pin number
    * @param pin_no: GPIO pin number
    * @retval none
*/
void GPIO_clear_interrupt(uint16_t pin_no){
    if(EXTI->PR & (1 << pin)){
        EXTI->PR |= 1 << pin;       //Writing 1 to the Pending register will clear the pending interrupt
    }
}
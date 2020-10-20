// This is a main application file main.c
//Implementing developed driver to blink LED to test the GPIO driver
#include "GPIO_Driver.h"
//#include "GPIO_Driver.c"
#include "main.h"

void led_init(void){
gpio_pin_conf_t led_pin_conf;
// enable clock for the GPIOD port to which LED's are connected
RCC->AHBIENR |= 1;
led_pin_conf.pin = LED_ORANGE;
led_pin_conf.mode = GPIO_PIN_OUTPUT_MODE;
led_pin_conf.op_type = GPIO_PIN_OP_TYPE_PUSHPULL;
led_pin_conf.SPEED = GPIO_PIN_SPEED_MEDIUM;
led_pin_conf.pull = GPIO_PIN_NO_PULL_PUSH;
GPIO_Init(GPIOD, &led_pin_conf);

led_pin_conf.pin = LED_GREEN;
GPIO_Init(GPIOD, &led_pin_conf);

led_pin_conf.pin = LED_RED;
GPIO_Init(GPIOD, &led_pin_conf);

led_pin_conf.pin = LED_BLUE;
GPIO_Init(GPIOD, &led_pin_conf);

}

_RCC_GPIOA_CLK_ENABLE();    //Enabling clock to Port A since button in STM32 board connected to PA0 and we are using button interrupt

//Configuring the interrupt
GPIO_configure_interrupt(GPIO_BUTTON_PIN, INT_FALLING_EDGE);

//Enabling the interrupt
GPIO_enable_interrupt(GPIO_BUTTON_PIN , IRQ_NUMBER);

/*
    *@brief Turns ON the LED which is connected to the given pin
    *@param *GPIOx: base address of the GPIO port
    *@param pin: pin number of the LED
    *@retval: None
*/
void led_turn_on(GPIO_TypeDef *GPIOx, uint16_t pin){
    GPIO_write_to_pin(GPIOD, pin, 1);
}

/*
    *@brief Turns OFF the LED which is connected to the given pin
    *@param *GPIOx: base address of the GPIO port
    *@param pin: pin number of the LED
    *@retval: None
*/
void led_turn_off(GPIO_TypeDef *GPIOx, uint16_t pin){
    GPIO_write_to_pin(GPIOD, pin, 0);
}

/*
    * @brief Toggles the led which is connected on the given pin
    * @param *GPIOx: base address of the GPIO port 
    * param pin: pin number of the LED
    * @retval: None
*/
void led_toggle(GPIO_TyprDef *GPIOx, uint16_t pin){
    if(GPIO_read_from_pin(GPIOx, pin)){
        GPIO_write_to_pin(GPIOD, pin, 0);
    }else{
        GPIO_write_to_pin(GPIOD, pin, 1);
    }
}

void EXTI0_IRQHandler(void){
GPIO_clear_interrupt(GPIO_BUTTON_PIN);  //Clearing the interrupt 
led_toggle(GPIO_TyprDef *GPIOx, uint16_t pin)
}

int main(){
    uint32_t i;

    /*Initializes the LED's */
    led_init();

    while(1){
            led_turn_on(GPIOD, LED_ORANGE);
            led_turn_on(GPIOD, LED_BLUE);

            for(i=0;i<500000;i++);

            led_turn_off(GPIOD, LED_ORANGE);
            led_turn_off(GPIOD, LED_ORANGE);

            for(i=0;i<500000;i++);
    }
    return 0;
}
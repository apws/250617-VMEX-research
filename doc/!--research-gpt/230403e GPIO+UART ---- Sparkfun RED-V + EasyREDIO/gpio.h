
// gpio.h
#ifndef _GPIO_H_
#define _GPIO_H_

// Define microcontroller family
//#define MCU_FAMILY_PIC
//#define MCU_FAMILY_AVR
//#define MCU_FAMILY_MSP430
#define MCU_FAMILY_STM32

#ifdef MCU_FAMILY_PIC
    // Include necessary headers and define register names for PIC
    #include <xc.h>
    #define TRIS_REG TRISB
    #define LAT_REG LATB
    #define PORT_REG PORTB
#elif defined(MCU_FAMILY_AVR)
    // Include necessary headers and define register names for AVR
    #include <avr/io.h>
    #define TRIS_REG DDRB
    #define LAT_REG PORTB
    #define PORT_REG PINB
#elif defined(MCU_FAMILY_MSP430)
    // Include necessary headers and define register names for MSP430
    #include <msp430.h>
    #define TRIS_REG P1DIR
    #define LAT_REG P1OUT
    #define PORT_REG P1IN
#elif defined(MCU_FAMILY_STM32)
    // Include necessary headers and define register names for STM32
    #include "stm32f1xx_hal.h"
    #define TRIS_REG GPIOB->MODER
    #define LAT_REG GPIOB->ODR
    #define PORT_REG GPIOB->IDR
#endif

void gpio_init(void);
void gpio_set_pin_direction(unsigned int pin, unsigned int direction);
void gpio_set_pin(unsigned int pin);
void gpio_clear_pin(unsigned int pin);
unsigned int gpio_read_pin(unsigned int pin);

#endif // _GPIO_H_

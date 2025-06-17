#include "stm32l4xx.h"

// Global variable to store the elapsed time in milliseconds
volatile uint32_t millis = 0;

// SysTick interrupt handler
void SysTick_Handler(void)
{
    millis++;   // Increment the elapsed time in milliseconds
}

// Delay function that blocks for the specified number of milliseconds
void delay(uint32_t ms)
{
    uint32_t start = millis;
    while ((millis - start) < ms);
}

int main(void)
{
    // Enable the relevant peripheral clocks
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;   // Enable GPIOB clock
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;  // Enable USART1 clock

    // Configure the system clock
    RCC->CR |= RCC_CR_HSION;    // Enable the internal RC oscillator (HSI)
    while (!(RCC->CR & RCC_CR_HSIRDY));   // Wait for HSI to be ready
    RCC->CFGR |= RCC_CFGR_SW_HSI;   // Switch to HSI as system clock source
    while (!(RCC->CFGR & RCC_CFGR_SWS_HSI));  // Wait for HSI to be used as system clock
    RCC->CR &= ~RCC_CR_PLLON;   // Disable the PLL
    while (RCC->CR & RCC_CR_PLLRDY);   // Wait for PLL to be disabled
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC_Msk;  // Clear the PLL source
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;  // Set the PLL source to HSI
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_Msk;   // Clear PLLM bits
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_1;  // Set PLLM to divide HSI by 2
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_Msk;   // Clear PLLN bits
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_16; // Set PLLN to multiply by 16
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLR_Msk;   // Clear PLLR bits
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLR_2;  // Set PLLR to divide by 4
    RCC->CR |= RCC_CR_PLLON;    // Enable PLL
    while (!(RCC->CR & RCC_CR_PLLRDY));  // Wait for PLL to be ready
    RCC->CFGR |= RCC_CFGR_SW_PLL;   // Switch to PLL as system clock source
    while (!(RCC->CFGR & RCC_CFGR_SWS_PLL));  // Wait for PLL to be used as system clock

    // Configure GPIO pins
    GPIOB->MODER &= ~GPIO_MODER_MODE13_Msk;   // Clear mode bits for PB13
    GPIOB->MODER |= GPIO_MODER_MODE13_0;  // Set PB13 to output mode

    GPIOA->MODER &= ~(GPIO_MODER_MODE9_Msk | GPIO_MODER_MODE10_Msk);   // Clear mode bits for PA9 and PA10
    GPIOA->MODER |= (GPIO_MODER_MODE9_1 | GPIO_MODER_MODE10_1);   // Set PA9 and PA10 to alternate function mode
    GPIOA->AFR[1] |= (7 << GPIO_AFRH_AFSEL9_Pos) | (7 << GPIO_AFRH_AFSEL10_Pos);   // Set alternate function to USART1

    // Configure the USART1 peripheral
    USART1->BRR = (520 << 4) | 5;   // Set the baud rate to 9600
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;   // Enable transmitter and receiver
    USART1->CR1 |= USART_CR1_UE;   // Enable USART1

    // Configure the SysTick timer to generate interrupts every millisecond
    SysTick->LOAD = 80000 - 1;  // Set the reload value to 80,000 (80 MHz / 1000 Hz)
    SysTick->VAL = 0;   // Clear the current value
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;  // Enable the SysTick timer with interrupts

    // Enable interrupts globally
    __enable_irq();

    while (1)
    {
        // Toggle PB13 every second
        GPIOB->ODR ^= GPIO_ODR_OD13;
        delay(1000);

        // Send data on USART1
        uint8_t adataToSend[] = "Hello, USART1!\n";
        for (int i = 0; i < sizeof(adataToSend); i++)
        {
            while (!(USART1->ISR & USART_ISR_TXE));   // Wait for TXE flag to be set
            USART1->TDR = adataToSend[i];   // Send the data byte
        }

//         // Send data on LPUART1
//         uint8_t bdataToSend[] = "Hello, LPUART1!\n";
//         for (int i = 0; i < sizeof(bdataToSend); i++)
//         {
//             while (!(LPUART1->ISR & USART_ISR_TXE));   // Wait for TXE flag to be set
//             LPUART1->TDR = bdataToSend[i];   // Send the data byte
//         }
    }
}


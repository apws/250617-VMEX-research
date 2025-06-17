
#ifndef W65C265S_H
#define W65C265S_H

#include <stdint.h>

// Memory-Mapped I/O Base Address for W65C265S Peripherals
#define IO_BASE 0x0000

// UART1 Registers
#define UART1_BASE (IO_BASE + 0x1C00)

typedef volatile struct {
    uint8_t U1_RBR_THR_DLL; // Receive Buffer Register (RBR) / Transmit Holding Register (THR) / Divisor Latch (Low)
    uint8_t U1_IER_DLH;     // Interrupt Enable Register (IER) / Divisor Latch (High)
    uint8_t U1_IIR_FCR;     // Interrupt Identification Register (IIR) / FIFO Control Register (FCR)
    uint8_t U1_LCR;         // Line Control Register
    uint8_t U1_MCR;         // Modem Control Register
    uint8_t U1_LSR;         // Line Status Register
    uint8_t U1_MSR;         // Modem Status Register
    uint8_t U1_SCR;         // Scratch Register
} W65C265S_UART1_TypeDef;

#define UART1 ((W65C265S_UART1_TypeDef *)UART1_BASE)

// ... Add other peripheral register definitions here

#endif // W65C265S_H


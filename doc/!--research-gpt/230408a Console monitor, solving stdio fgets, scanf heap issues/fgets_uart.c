
// uart_serial.h
#ifndef UART_SERIAL_H
#define UART_SERIAL_H

#include <stddef.h>

char *uart_fgets(char *s, int size);

#endif // UART_SERIAL_H




// uart_serial.c
#include "uart_serial.h"
#include "uart.h" // Assuming you have a UART library with a uart_read() function

char *uart_fgets(char *s, int size)
{
    if (size <= 0)
    {
        return NULL;
    }

    int i = 0;
    char c;
    while (i < (size - 1))
    {
        c = uart_read(); // Read a character from the UART

        if (c == '\r' || c == '\n') // Check for end of line
        {
            break;
        }

        s[i++] = c;
    }

    // Null-terminate the string
    s[i] = '\0';

    // Return the string if at least one character was read, otherwise return NULL
    return (i > 0) ? s : NULL;
}



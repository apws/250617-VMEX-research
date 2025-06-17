
// console.h
#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdarg.h>

void console_printf(const char *format, ...);

#endif // CONSOLE_H



// console.c
#include "console.h"
#include <stdio.h>

#ifdef EMBEDDED_PLATFORM
#include "serial.h" // Assuming you have a serial library for the embedded platform
#endif

void console_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    #ifdef EMBEDDED_PLATFORM
    // Assuming you have a serial_vprintf function in your serial library for the embedded platform
    serial_vprintf(format, args);
    #else
    vprintf(format, args);
    #endif

    va_end(args);
}



//sally-platform.h

#if OPTIMIZE==1
    #pragma GCC optimize("-Og")
#elif OPTIMIZE==2
    #pragma GCC optimize("-Os")
#elif OPTIMIZE==3
    #pragma GCC optimize("-Ofast")
#endif

#ifndef Arduino_h
    #include <Arduino.h> //Spresense conflict
#endif

#if defined(__arm__) || defined(ESP32) || defined(ESP8266)
#define PLATFORM_32
    #define RAMSIZE (16000)
#else
    #define RAMSIZE (2000)
#endif

//IDEA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// #ifndef BUFFER_LENGTH
//   #if (RAMSIZE < 256)
//     #define BUFFER_LENGTH 16
//   #elif (RAMSIZE < 4096)
//     #define BUFFER_LENGTH 32
//   #else
//     #define BUFFER_LENGTH 130
//   #endif
// #endif 


// Use INTERNAL_SRAM_SIZE instead of RAMEND - RAMSTART, which is vulnerable to a fencepost error. 

#ifdef PLATFORM_32
    #define PROGRAM_SIZE (RAMSIZE - 2400) //defacto not needed in case of unified types
#else
    #define PROGRAM_SIZE (RAMSIZE - 1200) //originally 1160
#endif

//STM32 compiler has menu options for OPTIMIZATIONS !!!
//with uploading via SWD STM32 WORKS !!!
//may be try FAST+LTO ???

// Enable memory alignment for 32bit processors
#ifdef PLATFORM_32
    #define ALIGN_MEMORY //required and works on NodeMCU and stm32g031-nucleo-32 !!!
#endif

#ifdef ALIGN_MEMORY
    // Align memory addess x to an even page
    #define ALIGN_UP(x) ((TU8 *)(((TU32)((x) + 1) >> 1) << 1))
    #define ALIGN_DOWN(x) ((TU8 *)(((TU32)(x) >> 1) << 1))
#else
    #define ALIGN_UP(x) x
    #define ALIGN_DOWN(x) x
#endif

// Use pgmspace/PROGMEM directive to store strings in progmem to save RAM
//#include <avr/pgmspace.h>

// some catches for AVR based text string stuff...
#ifndef PROGMEM
    #define PROGMEM
#endif
#ifndef pgm_read_byte
    #define pgm_read_byte(flash) *(flash)
#endif

#define VAR_SIZE sizeof(TS16) // Size of variables in bytes //sizeof(TVariable_S16)

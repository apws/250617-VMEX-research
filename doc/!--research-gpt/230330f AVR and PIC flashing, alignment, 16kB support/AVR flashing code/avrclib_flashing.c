
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdint.h>

// Function to write a word to the flash memory
static void write_flash_page(uint16_t address, uint16_t data)
{
    cli(); // Disable interrupts

    // Load the flash address to the address pointer (Z-register)
    asm volatile("movw %A0, %A1" "\n\t"
                 "movw %B0, %B1"
                 :
                 : "z"(address), "r"(data));

    // Write the word to the flash memory
    boot_page_fill(address, data);
    boot_page_write(address);
    boot_spm_busy_wait(); // Wait until the write operation finishes

    sei(); // Enable interrupts
}

void flash_write(uint16_t flash_address, const uint8_t *buffer, uint16_t size)
{
    uint16_t i;
    uint16_t end_address = flash_address + size;

    // Iterate over the buffer and write words to the flash memory
    for (i = flash_address; i < end_address; i += 2)
    {
        uint16_t data = buffer[i] | (buffer[i + 1] << 8);
        write_flash_page(i, data);
    }
}


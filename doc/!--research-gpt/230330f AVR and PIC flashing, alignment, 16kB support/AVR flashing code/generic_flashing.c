
#include <stdint.h>

// Extern assembly functions
extern void unlock_flash(void);
extern void lock_flash(void);
extern void erase_flash_page(uint32_t address);
extern void write_flash_word(uint32_t address, uint32_t data);

// Write buffer to flash memory
void flash_write(uint32_t flash_address, const uint8_t* buffer, uint32_t size)
{
    uint32_t i;
    uint32_t current_address = flash_address;
    uint32_t end_address = flash_address + size;

    // Unlock flash memory for writing
    unlock_flash();

    // Erase necessary flash pages
    for (i = flash_address; i < end_address; i += FLASH_PAGE_SIZE)
    {
        erase_flash_page(i);
    }

    // Write data to flash memory
    for (i = 0; i < size; i += 4)
    {
        uint32_t data = buffer[i] | (buffer[i + 1] << 8) | (buffer[i + 2] << 16) | (buffer[i + 3] << 24);
        write_flash_word(current_address, data);
        current_address += 4;
    }

    // Lock flash memory
    lock_flash();
}


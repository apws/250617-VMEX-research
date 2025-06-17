
#include <stdint.h>
#include <xc.h>

// Extern assembly functions
extern void unlock_flash(void);
extern void lock_flash(void);
extern void erase_flash_page(uint16_t address);
extern void write_flash_page(uint16_t address, const uint8_t* data, uint16_t size);

// Write buffer to flash memory
void flash_write(uint16_t flash_address, const uint8_t* buffer, uint16_t size)
{
    uint16_t i;
    uint16_t end_address = flash_address + size;

    // Unlock flash memory for writing
    unlock_flash();

    // Erase necessary flash pages and write data to flash memory
    for (i = flash_address; i < end_address; i += FLASH_PAGE_SIZE)
    {
        erase_flash_page(i);
        write_flash_page(i, buffer + (i - flash_address), FLASH_PAGE_SIZE);
    }

    // Lock flash memory
    lock_flash();
}


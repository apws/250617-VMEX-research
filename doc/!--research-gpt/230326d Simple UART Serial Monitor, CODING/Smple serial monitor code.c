#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// UART configuration functions
void uart_init(unsigned int baud_rate);
uint8_t uart_read();
void uart_write(uint8_t data);
void uart_print(const char *str);

#define BUFFER_SIZE 64
#define NUM_COMMANDS 3

// Example command functions
void command_led_on();
void command_led_off();
void command_print_help();

typedef struct {
    const char *name;
    void (*function)();
} command_t;

const command_t commands[NUM_COMMANDS] = {
    {"led_on", command_led_on},
    {"led_off", command_led_off},
    {"help", command_print_help},
};

void process_command(const char *buffer) {
    for (uint8_t i = 0; i < NUM_COMMANDS; i++) {
        if (strcmp(buffer, commands[i].name) == 0) {
            commands[i].function();
            return;
        }
    }
    uart_print("Unknown command. Type 'help' for a list of available commands.\r\n");
}

void command_led_on() {
    uart_print("LED turned ON\r\n");
}

void command_led_off() {
    uart_print("LED turned OFF\r\n");
}

void command_print_help() {
    uart_print("Available commands:\r\n");
    for (uint8_t i = 0; i < NUM_COMMANDS; i++) {
        uart_print(commands[i].name);
        uart_print("\r\n");
    }
}

int main() {
    uart_init(9600);
    char buffer[BUFFER_SIZE];
    uint8_t index = 0;

    uart_print("UART Serial Monitor Interpreter\r\nType 'help' for a list of available commands.\r\n");

    while (1) {
        uint8_t data = uart_read();
        uart_write(data); // Echo back the received character

        if (data == '\r' || data == '\n') {
            buffer[index] = '\0';
            if (index > 0) {
                process_command(buffer);
            }
            index = 0;
        } else if (index < BUFFER_SIZE - 1) {
            buffer[index++] = data;
        }
    }
}


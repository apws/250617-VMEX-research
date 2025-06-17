
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256
uint8_t firmware_buffer[BUFFER_SIZE];

uint8_t read_hex_digit(char ch) {
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    } else if (ch >= 'A' && ch <= 'F') {
        return ch - 'A' + 10;
    } else if (ch >= 'a' && ch <= 'f') {
        return ch - 'a' + 10;
    }
    return 0;
}

uint8_t read_hex_byte(char *str) {
    return (read_hex_digit(str[0]) << 4) | read_hex_digit(str[1]);
}

bool process_hex_packet(char *packet) {
    if (packet[0] != ':') {
        return false; // Invalid start character
    }

    uint16_t address = (read_hex_byte(packet + 1) << 8) | read_hex_byte(packet + 3);
    uint8_t data_length = read_hex_byte(packet + 5);

    if (address + data_length > BUFFER_SIZE) {
        return false; // Out of buffer bounds
    }

    uint8_t checksum = 0;
    for (int i = 0; i < data_length; ++i) {
        uint8_t data_byte = read_hex_byte(packet + 7 + i * 2);
        firmware_buffer[address + i] = data_byte;
        checksum += data_byte;
    }

    uint8_t received_checksum = read_hex_byte(packet + 7 + data_length * 2);
    return checksum == received_checksum;
}

void interactive_monitor() {
    char packet[64];
    size_t packet_index = 0;

    while (1) {
        char ch = uart_receive_char();

        if (ch == '\n' || ch == '\r') {
            if (packet_index > 0) {
                packet[packet_index] = '\0';
                bool success = process_hex_packet(packet);
                uart_send_string(success ? "OK\n" : "ERROR\n");
                packet_index = 0;
            }
        } else if (packet_index < sizeof(packet) - 1 && (isxdigit(ch) || ch == ':')) {
            packet[packet_index++] = ch;
        } else {
            // Invalid character, reset packet
            packet_index = 0;
        }
    }
}


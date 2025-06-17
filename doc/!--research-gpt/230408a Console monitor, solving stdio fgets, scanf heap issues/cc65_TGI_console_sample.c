
#include <conio.h>
#include <stdio.h>

void main(void) {
    char input;

    // Set up the text screen
    clrscr();
    bgcolor(COLOR_BLACK);
    textcolor(COLOR_WHITE);
    cursor(1);

    // Print an introduction message
    cputs("Commodore Plus/4 Terminal\r\n");
    cputs("=========================\r\n");
    cputs("Type anything and press Enter.\r\n");
    cputs("Type 'q' and press Enter to quit.\r\n");
    cputs("\r\n> ");

    // Main input loop
    while (1) {
        input = cgetc(); // Wait for a key press
        cputc(input);    // Print the entered character

        // Check for the Enter key or 'q' key
        if (input == '\r') {
            cputs("\r\n> ");
        } else if (input == 'q') {
            break;
        }
    }

    // Clear the screen and print an exit message
    clrscr();
    cputs("Goodbye!\r\n");
}


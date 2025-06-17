
#include <tgi.h>
#include <conio.h>

// Declare TGI driver for Plus/4
extern char plus4tgi[];

void main(void) {
    // Install and initialize the TGI driver
    tgi_install(plus4tgi);
    tgi_init();
    while (tgi_busy()); // Wait for the driver to finish initializing

    tgi_clear(); // Clear the screen

    // Draw a line
    tgi_setcolor(TGI_COLOR_WHITE);
    tgi_line(20, 20, 100, 20);

    // Draw a rectangle
    tgi_setcolor(TGI_COLOR_CYAN);
    tgi_rectangle(30, 30, 80, 50);

    // Draw a circle
    tgi_setcolor(TGI_COLOR_YELLOW);
    tgi_circle(100, 100, 20);

    tgi_updatedisplay(); // Refresh the screen

    // Wait for a keypress to exit
    cgetc();

    // Deinitialize TGI and uninstall the driver
    tgi_deinit();
    tgi_uninstall();
}


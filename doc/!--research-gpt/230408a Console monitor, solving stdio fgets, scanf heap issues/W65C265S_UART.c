
#include "w65c265s.h"

int main(void) {
    // Example: Set the UART1 Line Control Register
    UART1->U1_LCR = 0x03;

    // ... Add your application code here

    return 0;
}


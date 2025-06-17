
#include <stdio.h>
#include <string.h>

// Include VMEX header and other headers

// Core structure and other definitions

// ...

// Function prototypes
void print_registers(Core *core);
void process_command(Core *core, const char *command);
void monitor(Core *core);
int tests(); // Assuming this function is defined elsewhere

int main(int argc, char *argv[])
{
    // Check for "/test" argument
    if (argc > 1 && strcmp(argv[1], "/test") == 0)
    {
        return tests();
    }
    else
    {
        TU8 testprog[] =
        {
            0x11, 0x10, 0x00, 0x00, // addi r1 r0 0
            0x11, 0x10, 0x05, 0x00, // addi r1 r0 5
        };

        return vmex(testprog, sizeof(testprog));
    }
}


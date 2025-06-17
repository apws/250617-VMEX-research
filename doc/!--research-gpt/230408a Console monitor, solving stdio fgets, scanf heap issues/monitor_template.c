
#include <stdio.h>
#include <string.h>

// Include VMEX header and other headers

// Core structure and other definitions

// ...

// Function prototypes
void print_registers(Core *core);
void process_command(Core *core, const char *command);
void monitor(Core *core);

int vmex(const TU8 testprog[], int progsize)
{
    // Initialize the core
    // ...

    // Load the testprog into the core's prog memory
    memcpy(core.prog, testprog, progsize);

    // Run the monitor REPL loop
    monitor(&core);

    return 0;
}

void monitor(Core *core)
{
    char command[32];
    while (1)
    {
        printf("> ");
        fgets(command, sizeof(command), stdin);

        // Remove the newline character from the input
        command[strcspn(command, "\n")] = 0;

        // Process the entered command
        process_command(core, command);
    }
}

void print_registers(Core *core)
{
    for (int i = 0; i < 16; i++)
    {
        printf("R%d: 0x%08X\n", i, core->regs[i]);
    }
}

void process_command(Core *core, const char *command)
{
    if (strcmp(command, "r") == 0)
    {
        print_registers(core);
    }
    else
    {
        printf("Unknown command: %s\n", command);
    }
}


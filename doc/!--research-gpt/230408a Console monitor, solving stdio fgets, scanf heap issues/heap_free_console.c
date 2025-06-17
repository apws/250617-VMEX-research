
int custom_getc(void)
{
    // Implement reading a character from your hardware
    int ch = 0; // Replace this with the actual character read from your hardware
    return ch;
}

void custom_putc(char c)
{
    // Implement writing a character to your hardware
    // 'c' is the character to be written
    // Add your hardware-specific code to send the character
}



void monitor(Core *core)
{
    char command[32];
    while (1)
    {
        printf("> ");
        int i = 0;
        while (1)
        {
            int ch = custom_getc();
            if (ch == '\n' || ch == '\r')
            {
                break;
            }
            if (i < sizeof(command) - 1)
            {
                command[i++] = (char)ch;
            }
        }
        command[i] = 0; // Terminate the command string

        // Process the entered command
        process_command(core, command);
    }
}




using System.Runtime.InteropServices;

public unsafe struct Core
{
    public fixed int regs[16];
    public fixed byte rsvd[42 * 4];
    public int pc;
    public fixed byte data[DATA_SIZE];
    public fixed byte prog[PROG_SIZE];
}

public class Vmex
{
    static Core core;

    static Vmex()
    {
        // Initialize core to all zeroes
        core = new Core();
    }

    // Rest of the class
}


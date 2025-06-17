
using System;
using System.Runtime.InteropServices;

public class Vmex
{
    byte[] coreProg = new byte[256];
    int corePc = 0;

    public int VmexFunction(byte[] testProg, int progSize)
    {
        byte opcode = 0;
        byte rs1 = 0;
        byte rs2 = 0;
        byte rd = 0;
        int imm = 0;

        int r10i = 0;

        Buffer.BlockCopy(testProg, 0, coreProg, 0, progSize);

        int pc = 0;

        while (pc < progSize)
        {
            pc = corePc;

            byte[] _op_ = new byte[3] { coreProg[pc], coreProg[pc + 1], coreProg[pc + 2] };
            opcode = _op_[0];

            switch (opcode & 0xF0)
            {
                case R3_TYPE:
                case R2_TYPE:
                case RC_TYPE:
                case RD_TYPE:
                    {
                        rd = (byte)(_op_[1] >> 4);
                        rs1 = (byte)(_op_[2] >> 4);
                        break;
                    }
            }
            // rest of the code
        }
        // rest of the code
    }

    // rest of the class
}


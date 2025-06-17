
case IE_TYPE:
{
    rd = (byte)(_op_[1] >> 4);
    rs1 = (byte)(_op_[1] & 0xF);
    imm = *((ushort*)(_op_ + 2)); // Read 16-bit immediate value directly
    break;
}


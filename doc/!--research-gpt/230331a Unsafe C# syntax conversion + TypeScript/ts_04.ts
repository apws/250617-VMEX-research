

case IE_TYPE:
{
    rd = (_op_[1] >> 4) & 0xFF;
    rs1 = _op_[1] & 0xF;
    imm = (_op_[pc + 2] | (_op_[pc + 3] << 8)) >>> 0; // Read 16-bit immediate value directly
    break;
}


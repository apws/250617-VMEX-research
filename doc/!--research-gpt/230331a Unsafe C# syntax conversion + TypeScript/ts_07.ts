
// DATA MEMORY ACCESS ---------------------------------------------------------------
// TEST
case OPIA1_LB:
    {
        const offset = _reg_[rs1] + imm;
        _reg_[rd] = _data_[offset] << 24 >> 24; // Sign extension for 8-bit value
    }
    break;

// TEST
case OPIA2_LH:
    {
        const offset = _reg_[rs1] + imm;
        _reg_[rd] = (_data_[offset] | (_data_[offset + 1] << 8)) << 16 >> 16; // Sign extension for 16-bit value
    }
    break;

// TEST
case OPIA4_LW:
    {
        const offset = _reg_[rs1] + imm;
        _reg_[rd] = _data_[offset] | (_data_[offset + 1] << 8) | (_data_[offset + 2] << 16) | (_data_[offset + 3] << 24);
    }
    break;



const dataView = new DataView(_data_.buffer);

// DATA MEMORY ACCESS ---------------------------------------------------------------
// TEST
case OPIA1_LB:
    {
        const offset = _reg_[rs1] + imm;
        _reg_[rd] = dataView.getInt8(offset);
    }
    break;

// TEST
case OPIA2_LH:
    {
        const offset = _reg_[rs1] + imm;
        _reg_[rd] = dataView.getInt16(offset, true); // Assuming little-endian byte order
    }
    break;

// TEST
case OPIA4_LW:
    {
        const offset = _reg_[rs1] + imm;
        _reg_[rd] = dataView.getInt32(offset, true); // Assuming little-endian byte order
    }
    break;


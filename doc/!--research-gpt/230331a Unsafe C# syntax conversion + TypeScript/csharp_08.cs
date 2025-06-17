
// DATA MEMORY ACCESS ---------------------------------------------------------------
// TEST
case OPIA1_LB:
    {
        byte* ptr = _data_ + _reg_[rs1] + imm;
        _reg_[rd] = *(sbyte*)ptr;
    }
    break;

// TEST
case OPIA2_LH:
    {
        byte* ptr = _data_ + _reg_[rs1] + imm;
        _reg_[rd] = *(short*)ptr;
    }
    break;

// TEST
case OPIA4_LW:
    {
        byte* ptr = _data_ + _reg_[rs1] + imm;
        _reg_[rd] = *(int*)ptr;
    }
    break;



// DATA MEMORY ACCESS ---------------------------------------------------------------
// TEST
case OPIA1_LB:
    {
        TU8* ptr = _data_ + _reg_[rs1] + imm;
        _reg_[rd] = *(TS8*)ptr;
    }
    break;

// TEST
case OPIA2_LH:
    {
        TU8* ptr = _data_ + _reg_[rs1] + imm;
        _reg_[rd] = *(TS16*)ptr;
    }
    break;

// TEST
case OPIA4_LW:
    {
        TU8* ptr = _data_ + _reg_[rs1] + imm;
        _reg_[rd] = *(TS32*)ptr;
    }
    break;


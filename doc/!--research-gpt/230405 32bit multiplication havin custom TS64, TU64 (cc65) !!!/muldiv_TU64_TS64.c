
            #ifdef MULDIV
            //OP R2-TYPE // "M" extension = multiply/divide //!!! takes 2-10kB at -Os, half of the VMEX !!!!
            case OPR21_MUL:
                #ifdef SWMULDIV
                *_rd_ = mul(*_rs1_, *_rs2_);
                #else
                {
                    *_rd_ = *_rs1_ * *_rs2_;
                }
                #endif
                break;

            case OPR22_MULH:
                #ifdef SWMULDIV
                *_rd_ = mulh(*_rs1_, *_rs2_);
                #else
                {
                     TS64 result = (TS64)*_rs1_ * (TS64)*_rs2_;
                     *_rd_ = (TS32)(result >> 32);
                }
                #endif
                break;

            case OPR23_MULHU:
                #ifdef SWMULDIV
                *_rd_ = mulhu(*_rs1_, *_rs2_);
                #else
                {
                    TU64 result = (TU64)*_rs1_ * (TU64)*_rs2_;
                    *_rd_ = (TS32)(result >> 32);
                }
                #endif
                break;

            case OPR24_MULHSU:
                #ifdef SWMULDIV
                *_rd_ = mulhsu(*_rs1_, *_rs2_);
                #else
                {
                    TS64 result = (TS64)*_rs1_ * (TU64)*_rs2_;
                    *_rd_ = (TS32)(result >> 32);
                }
                #endif
                break;

            case OPR25_DIV:
                *_rd_ = *_rs1_ / *_rs2_;
                break;

            case OPR26_DIVU:
                *_rd_ = (TU32)*_rs1_ / (TU32)*_rs2_;
                break;

            case OPR27_REM:
                *_rd_ = *_rs1_ % *_rs2_;
                break;

            case OPR28_REMU:
                *_rd_ = (TU32)*_rs1_ % (TU32)*_rs2_;
                break;
            #endif


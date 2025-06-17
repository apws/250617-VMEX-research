
// Define constants
const OPIA1_LB = /* value */;
const OPIA2_LH = /* value */;
const OPIA4_LW = /* value */;

// Replace with actual typed arrays
let _data_: Uint8Array = /* your Uint8Array */;
let _reg_: Int32Array = /* your Int32Array */;

let imm: number = /* your value */;

switch (opcode) {
    // DATA MEMORY ACCESS ---------------------------------------------------------------
    // TEST
    case OPIA1_LB:
        {
            let index = _reg_[rs1] + imm;
            _reg_[rd] = _data_[index] << 24 >> 24; // Sign-extend 8-bit value to 32-bit
        }
        break;

    // TEST
    case OPIA2_LH:
        {
            let index = _reg_[rs1] + imm;
            _reg_[rd] = (_data_[index] | (_data_[index + 1] << 8)) << 16 >> 16; // Sign-extend 16-bit value to 32-bit
        }
        break;

    // TEST
    case OPIA4_LW:
        {
            let index = _reg_[rs1] + imm;
            _reg_[rd] = _data_[index] | (_data_[index + 1] << 8) | (_data_[index + 2] << 16) | (_data_[index + 3] << 24); // Combine 4 bytes into a 32-bit value
        }
        break;
}



const DATA_SIZE = /* your value */;
const PROG_SIZE = /* your value */;

class Core {
    regs: Int32Array;
    rsvd: Uint8Array;
    pc: number;
    data: Uint8Array;
    prog: Uint8Array;

    constructor() {
        this.regs = new Int32Array(16);
        this.rsvd = new Uint8Array(42 * 4);
        this.pc = 0;
        this.data = new Uint8Array(DATA_SIZE);
        this.prog = new Uint8Array(PROG_SIZE);
    }
}

class Vmex {
    static core: Core;

    constructor() {
        // Initialize core to all zeroes
        Vmex.core = new Core();
    }

    public vmexFunction(testProg: Uint8Array, progSize: number): number {
        let opcode: number = 0;
        let rs1: number = 0;
        let rs2: number = 0;
        let rd: number = 0;
        let imm: number = 0;
        let pc: number = 0;

        let r10i: number = 0;

        let _core_: Core = Vmex.core;

        let _reg_: Int32Array = _core_.regs;
        let _prog_: Uint8Array = _core_.prog;
        let _data_: Uint8Array = _core_.data;

        // Fill program
        _prog_.set(testProg.subarray(0, progSize));

        while (pc < progSize) {
            pc = _core_.pc;

            let _op_: number = _prog_[pc];
            opcode = _op_;

            // Rest of the code
        }

        // Rest of the code

        return /* return value */;
    }

    // Rest of the class
}



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

    static initialize() {
        // Initialize core to all zeroes
        Vmex.core = new Core();
    }

    // Rest of the class
}

// Call the static initialize method to initialize the core
Vmex.initialize();


typedef struct {
    TU32 low;
    TU32 high;
} TU64X;

typedef struct {
    TU32 low;
    TS32 high;
} TS64X;

// Function to multiply two unsigned 32-bit integers and return a 64-bit result
TU64X mul_TU32(TU32 a, TU32 b) {
    TU64X result;
    TU32 a_low = a & 0xFFFF;
    TU32 a_high = a >> 16;
    TU32 b_low = b & 0xFFFF;
    TU32 b_high = b >> 16;

    TU32 low_low = a_low * b_low;
    TU32 low_high = a_low * b_high;
    TU32 high_low = a_high * b_low;
    TU32 high_high = a_high * b_high;

    result.low = low_low;
    result.high = high_high;

    TU32 mid1 = low_high << 16;
    TU32 mid2 = high_low << 16;

    result.low += mid1;
    if (result.low < mid1) {
        result.high++;
    }

    result.low += mid2;
    if (result.low < mid2) {
        result.high++;
    }

    result.high += low_high >> 16;
    result.high += high_low >> 16;

    return result;
}

// Function to multiply two signed 32-bit integers and return a 64-bit result
TS64X mul_TS32(TS32 a, TS32 b) {
    TS64X result;
    TU32 a_unsigned = (TU32)a;
    TU32 b_unsigned = (TU32)b;
    TU64X mul_unsigned = mul_TU32(a_unsigned, b_unsigned);
    result.low = mul_unsigned.low;
    result.high = mul_unsigned.high;

    // Adjust the sign
    if (a < 0) {
        result.high -= b_unsigned;
    }
    if (b < 0) {
        result.high -= a_unsigned;
    }

    return result;
}

TS32 mul(TS32 a, TS32 b) {
    TS64X result = mul_TS32(a, b);
    return (TS32)result.low;
}

TS32 mulh(TS32 a, TS32 b) {
    TS64X result = mul_TS32(a, b);
    return result.high;
}

TU32 mulhu(TU32 a, TU32 b) {
    TU64X result = mul_TU32(a, b);
    return result.high;
}

TS32 mulhsu(TS32 a, TU32 b) {
    TS64X result = mul_TS32(a, (TS32)b);
    return result.high;
}

//sally-stack.h


static void PushByte(TU8 b);
static TU8 PopByte();


#define STACK_DEPTH 5
#define STACK_SIZE (sizeof(struct SForFrame) * STACK_DEPTH)

struct SForFrame {
    TChar frameType;

    TChar forVariable;
    TS16 toValue;
    TS16 stepValue;
    
    TU8 *currentLinePtr;
    TU8 *positionPtr;
};
#define STACK_FOR_FLAG 'F'


struct SCallFrame {
    TChar frameType;

    TU8 *currentLinePtr;
    TU8 *positionPtr;
};
#define STACK_CALL_FLAG 'G'


static void PushByte(TU8 byte)
{
    gsStackPtr--;
    *gsStackPtr = byte;
}


static TU8 PopByte()
{
    TU8 byte;
    byte = *gsStackPtr;
    gsStackPtr++;
    return byte;
}

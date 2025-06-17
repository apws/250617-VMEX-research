//sally-write.h

void WriteNumber(TS16 num);
void WriteUnsignedNumber(TU16 num);
static TBool IsWriteQuotedString(void);
void WriteListProgramLine();


void WriteNumber(TS16 num)
{
    TU8 digits = 0;

    if (num < 0)
    {
        num = -num;
        ConsoleOutput('-');
    }
    do
    {
        PushByte(num%10+'0');
        num = num/10;
        digits++;
    }
    while (num > 0);

    while (digits > 0)
    {
        ConsoleOutput(PopByte());
        digits--;
    }
}


void WriteUnsignedNumber(TU16 num)
{
    TU8 digits = 0;

    do
    {
        PushByte(num%10+'0');
        num = num/10;
        digits++;
    }
    while (num > 0);

    while (digits > 0)
    {
        ConsoleOutput(PopByte());
        digits--;
    }
}


static TBool IsWriteQuotedString(void)
{
    TU8 i=0;
    TU8 delim = *gsPositionPtr;
    
    if (delim != CH_DOUBLE_QUOTE && delim != CH_SINGLE_QUOTE)
        return false;
    gsPositionPtr++;

    // Check we have a closing delimiter
    while (gsPositionPtr[i] != delim)
    {
        if (gsPositionPtr[i] == CH_NEWLINE)
            return false;
        i++;
    }

    // Print the characters
    while (*gsPositionPtr != delim)
    {
        ConsoleOutput(*gsPositionPtr);
        gsPositionPtr++;
    }
    gsPositionPtr++; // Skip over the last delimiter

    return true;
}


void WriteListProgramLine()
{
    TLineNum_U16 line_num;

    line_num = *((TLineNum_U16 *)(gsListProgramLinePtr));
    gsListProgramLinePtr += sizeof(TLineNum_U16) + sizeof(TU8);

    // Output the line */
    WriteNumber(line_num);
    ConsoleOutput(' ');
    while (*gsListProgramLinePtr != CH_NEWLINE)
    {
        ConsoleOutput(*gsListProgramLinePtr);
        gsListProgramLinePtr++;
    }
    gsListProgramLinePtr++;

#ifdef ALIGN_MEMORY
    // Start looking for next line on even page
    if (ALIGN_UP(gsListProgramLinePtr) != gsListProgramLinePtr)
        gsListProgramLinePtr++;
#endif

    WriteLn();
}

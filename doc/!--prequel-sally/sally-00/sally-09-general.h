//sally-general.h

static void ParseWhitespace(void);
static void ScanTableIndex(const TU8 *tablePtr); //TTableKey
static TU16 ParseNumber(void); //TVariable_S16 ???
static TU8 *FindLinePtr(void);
static void LineBufferToUppercase(void);


static void ParseWhitespace(void)
{
    while (*gsPositionPtr == CH_SPACE)
        gsPositionPtr++;
}


static void ScanTableIndex(const TU8 *tablePtr)
{
    TU16 i = 0;
    gsTableIndex = 0;

    while (true)
    {
        // Run out of table entries?
        if (pgm_read_byte(tablePtr) == 0)
            return;

        // Do we match this character?
        if (gsPositionPtr[i] == pgm_read_byte(tablePtr))
        {
            i++;
            tablePtr++;
        }
        else
        {
            // do we match the last character of keyword (with 0x80 added)? If so, return
            if (gsPositionPtr[i]+0x80 == pgm_read_byte(tablePtr))
            {
                gsPositionPtr += i+1;  // Advance the pointer to following the keyword
                ParseWhitespace();
                return;
            }

            // Forward to the end of this keyword
            while ((pgm_read_byte(tablePtr) & 0x80) == 0)
                tablePtr++;

            // Now move on to the first character of the next word, and reset the position index
            tablePtr++;
            gsTableIndex++;
            ParseWhitespace();
            i = 0;
        }
    }
}


static TU16 ParseNumber(void)
{
    TU16 num = 0;
    ParseWhitespace();

    while (*gsPositionPtr >= '0' && *gsPositionPtr <= '9')
    {
        // Trap overflows
        if (num >= TU16_MAX/10)
        {
            num = TU16_MAX; //mixworx MAX TS16/TU16
            break;
        }

        num = num *10 + *gsPositionPtr - '0';
        gsPositionPtr++;
    }
    return num;
}


static TU8 *FindLinePtr(void)
{
    TU8 *linePtr = gsProgramBeginPtr;
    while (true)
    {
        if (linePtr == gsProgramEndPtr)
            return linePtr;

        if (((TLineNum_U16 *)linePtr)[0] >= gsLineNumber)
            return linePtr;

        // Add the line length onto the current address, to get to the next line;
        linePtr += linePtr[sizeof(TLineNum_U16)];
    }
}


// static void LineBufferToUppercase(void)
// {
//     TU8 *ch = gsProgramEndPtr + sizeof(TLineNum_U16);
//     TU8 quote = 0;

//     while (*ch != CH_NEWLINE)
//     {
//         // Are we in a quoted string?
//         if (*ch == quote)
//             quote = 0;
//         else if (*ch == CH_DOUBLE_QUOTE || *ch == CH_SINGLE_QUOTE)
//             quote = *ch;
//         else if (quote == 0 && *ch >= 'a' && *ch <= 'z')
//             *ch = *ch + 'A' - 'a';
//         ch++;
//     }
// }


//sally-messages.h

void MessageWrite(const TChar* msgPtr);
void MessageWriteLn(const TChar* msgPtr);


static const TChar msgInit[]           PROGMEM = "\n\nSALLY " VERSION;
static const TChar msgBytesFree[]      PROGMEM = " bytes free.";

static const TChar msgOK[]             PROGMEM = "OK";
static const TChar msgSyntaxError[]    PROGMEM = "Syntax?: ";
static const TChar msgArgumentError[]  PROGMEM = "Argument?";
static const TChar msgFailureError[]   PROGMEM = "!FAILURE!";
static const TChar msgBreak[]          PROGMEM = "!BREAK!";

//static const TChar msg_unimplimented[] PROGMEM = "Unimplemented";
//static const TChar msg_backspace[]     PROGMEM = "\b \b";


void MessageWrite(const TChar *msgPtr)
{
    while (pgm_read_byte(msgPtr) != 0)
    {
        ConsoleOutput( pgm_read_byte(msgPtr++) );
    };
}


void MessageWriteLn(const TChar *msgPtr)
{
    MessageWrite(msgPtr);
    WriteLn();
}


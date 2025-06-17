//sally-console.h

static TBool IsConsoleBreak(void);
static TChar ConsoleInput();
static void ConsoleOutput(TChar c);
static void WriteLn(void);

void XDBG(TChar ch);


static void ConsoleInit()
{
    CONSOLE_PORT.begin(CONSOLE_BAUD);	// opens serial port
    while (!CONSOLE_PORT); // for Leonardo //FIXME this blocks running sketch WITHOUT TERMINAL ??!!
    //delay(2000);
    //infineon SERIAL_BUFFER_SIZE , HardwareSerial setInterruptPriority ??????

}

static TBool IsConsoleBreak(void)
{
  if (CONSOLE_PORT.available())
    return CONSOLE_PORT.read() == CTRLC;
  return false;
}


static TChar ConsoleInput()
{
    switch (gsInStream)
    {
      case kStreamFile:
          break;

      case kStreamEEProm:
          break;

      case kStreamSerial:
      default:
          while (true)
          {
              if (CONSOLE_PORT.available())
                  return CONSOLE_PORT.read();
          }
      }

    gsInStream = kStreamSerial;
    inhibitOutput = false;

    return CH_NEWLINE; // trigger a prompt.
}


static void ConsoleOutput(TChar c)
{
  if (inhibitOutput) return;
#ifdef CONSOLE_XMC2GO
  //NO https://www.arduino.cc/reference/en/language/functions/communication/serial/availableforwrite/
  while (!CONSOLE_PORT)
#endif
  CONSOLE_PORT.write(c);
}


static void WriteLn(void)
{
  ConsoleOutput(CH_NEWLINE);
  //ConsoleOutput(CR); //mixworx //termite OK
}


void XDBG(TChar ch)
{
#ifdef XDBG_ON
    //NO https://www.arduino.cc/reference/en/language/functions/communication/serial/availableforwrite/
    while (!CONSOLE_PORT)
    CONSOLE_PORT.write('|'); CONSOLE_PORT.write(ch); CONSOLE_PORT.write('|');
#endif
}

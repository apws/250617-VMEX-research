//sally-read.h

static void ReadLine(TChar prompt)
{
    ConsoleOutput(prompt);
    gsPositionPtr = gsProgramEndPtr + sizeof(TLineNum_U16);

    while (true)
    {
        TChar ch = ConsoleInput();
        
        switch (ch)
        {
          case CH_NEWLINE:
          case CR: //REQUIRED - list pasting support into terminal !!!
              WriteLn();
              // Terminate all strings with a CH_NEWLINE
              gsPositionPtr[0] = CH_NEWLINE; //mixworx *gsPositionPtr = CH_NEWLINE ????
              return;

          // case CTRLH:
          //     if (gsPositionPtr == gsProgramEndPtr)
          //         break;
          //     gsPositionPtr--;
          //     MessageWriteLn(msg_backspace);
          //     break;

          default:
              // We need to leave at least one space to allow us to shuffle the line into order
              if (gsPositionPtr == gsVarBeginPtr - 2) //FIXME //mixworx literal
                  ConsoleOutput(BELL);
              else
              {
                  gsPositionPtr[0] = ch;  //mixworx *gsPositionPtr = ch ???
                  gsPositionPtr++;
                  ConsoleOutput(ch);
              }
        }
    }
}


//SALLY - totally 1_800 lines of C code

//sally-00.ino

#define VERSION "v220202d"

#define OPTIMIZE 1
//#define XDBG_ON //optimize 1=Og 2=Os 3=Ofast

//Termite settings: Append LF (compatible to TBA now)
#define CONSOLE_PORT Serial
#define CONSOLE_BAUD (2400)
//#define CONSOLE_BAUD (9600)
//#define CONSOLE_XMC2GO //needs 9600 !!! XMC2GO SERIAL UNRELIABLE AS HELL !!!


#include "sally-01-platform.h"
#include "sally-02-typedefs.h"

#include "sally-03-tables.h"
#include "sally-04-globals.h"
#include "sally-05-stack.h"
#include "sally-06-chars.h"
#include "sally-07-console.h" //XDBG
#include "sally-08-messages.h"

#include "sally-09-general.h"
#include "sally-10-expressions.h"
#include "sally-11-read.h"
#include "sally-12-write.h"


//!!!!!!! INTERESTING 
//this code NEVER uses "for" loop, only "while" !!!! so, why to have it in SALLY ???
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//DEFINE HERE OWN MEMCPY where possible https://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm
//ITS QUESTION IF WILL BE BETTER TO CALL LIBRARY MEMCPY OR NOT
//BENCHMARK - we need to have some menchmark SALLY code !!!!!!!!!!!


//--- SETUP ----------------------------------------------------------------------------------------
void setup()
{
    ConsoleInit();
    MessageWriteLn(msgInit);
}


//--- LOOP ----------------------------------------------------------------------------------------
void loop()
{
    TU8 *programStartPtr;
    TU8 *newProgramEndPtr;
    TU8 lineLenght;

    TBool isDigital; //lib arduino - weird here 

    TS16 val;        //FIXME mixworx - its sometimes re-declared as LOCAL in block ???
                     //all locals are on STACK, so SLOWER than existing globals, sure !!!

    gsProgramBeginPtr = gsProgramBuffer;
    gsProgramEndPtr = gsProgramBeginPtr;
    gsStackPtr = gsProgramBuffer + sizeof(gsProgramBuffer);  // Needed for WriteNumber

    gsStackLimitPtr = ALIGN_DOWN(gsProgramBuffer + sizeof(gsProgramBuffer) - STACK_SIZE);
    gsVarBeginPtr = ALIGN_DOWN(gsStackLimitPtr - 27*VAR_SIZE); //A-Z 27 S16 variables only here !!!

    //INTERPRETER INIT - WRITE BYTES FREE
    WriteNumber(gsVarBeginPtr - gsProgramEndPtr);
    MessageWriteLn(msgBytesFree);


//INTERPRETER REPL
lbl_warmStart:
    // this signifies that it is running in DIRECT mode.
    gsCurrentLinePtr = 0; //mixworx NULL ???
    gsStackPtr = gsProgramBuffer + sizeof(gsProgramBuffer);
    MessageWriteLn(msgOK);

lbl_prompt:
    if (gsIsTriggerRun)
    {
        gsIsTriggerRun = false;
        gsCurrentLinePtr = gsProgramBeginPtr;
        goto lbl_execLine;
    }

    //PROMPT
    ReadLine(CH_DIRECT_PROMPT);
    //LineBufferToUppercase(); //WARN mixworx - variables MUST be uppercase
    
    //PROCESSING ENTERED LINE
    gsPositionPtr = gsProgramEndPtr + sizeof(TU16);

    // Find the end of the freshly entered line
    while (*gsPositionPtr != CH_NEWLINE)
        gsPositionPtr++;

    //FIXME //MEMCPY? mixworx
    // Move it to the end of program_memory
    {
        TU8 *dest;
        dest = gsVarBeginPtr - 1;
        while (true)
        {
            *dest = *gsPositionPtr;
            if (gsPositionPtr == gsProgramEndPtr + sizeof(TU16))
                break;

            dest--;
            gsPositionPtr--;
        }
        gsPositionPtr = dest;
    }

    //IS LINE NUMBER ???
    gsLineNumber = ParseNumber();
    //ParseWhitespace(); //WARN mixworx - we preserve leading whitespaces in program (indentation) stored in RAM, OKAY for now
    if (*gsPositionPtr == CH_SPACE) 
        gsPositionPtr++; //mixworx, parse SINGLE whitespace instead

    //DIRECT COMMAND
    if (gsLineNumber == 0)
        goto lbl_direct;

    // if (gsLineNumber == TU16_MAX) //mixworx, weird
    //     goto error_Argument;


    //ENTER NUMBERED LINE INTO PROGRAM OR DELETE LINE
    // Find the length of what is left, including the (yet-to-be-populated) line header
    lineLenght = 0;
    while (gsPositionPtr[lineLenght] != CH_NEWLINE)
        lineLenght++;
    lineLenght++; // Include the CH_NEWLINE in the line length
    lineLenght += sizeof(TU16) + sizeof(TU8); // Add space for the line number and line length

    // Now we have the number, add the line header.
    gsPositionPtr -= 3; //FIXME ???? - pokud mozno odstranit veskere LITERALY => KONSTANTY, sizeof !!!


#ifdef ALIGN_MEMORY
    // Line starts should always be on 16-bit pages //FIXME //WARN //DEBUG mixworx HERE 16bit !!??!!?? we align to TU32 !!!
    if (ALIGN_DOWN(gsPositionPtr) != gsPositionPtr) //HERE is the alignment check !!!
    {
        gsPositionPtr--;
        lineLenght++;
        // As the start of the line has moved, the data should move as well
        TU8 *bytesToMove;
        bytesToMove = gsPositionPtr + 3;
        //FIXME //MEMCPY mixworx ?????????????
        while (bytesToMove < gsPositionPtr + lineLenght - 1)
        {
            *bytesToMove = *(bytesToMove + 1);
            bytesToMove++;
        }
    }
#endif

    *((TU16 *)gsPositionPtr) = gsLineNumber; //WARN mixworx, single occurence of casting gsPositionPtr to 16bit
    gsPositionPtr[sizeof(TLineNum_U16)] = lineLenght;

    // Merge program line into the rest of the program
    programStartPtr = FindLinePtr();

    //DELETE EXISTING LINE
    // If a program line with that number exists, then remove it
    //FIXME //MEMCPY? mixworx
    if (programStartPtr != gsProgramEndPtr && *((TLineNum_U16 *)programStartPtr) == gsLineNumber)
    {
        TU8 *dest, *from;
        TU16 bytesToMove;

        from = programStartPtr + programStartPtr[sizeof(TLineNum_U16)];
        dest = programStartPtr;

        //FIXME //MEMCPY mixworx
        bytesToMove = gsProgramEndPtr - from;
        while (bytesToMove > 0)
        {
            *dest = *from;
            from++;
            dest++;
            bytesToMove--;
        }
        gsProgramEndPtr = dest;
    }

    if (gsPositionPtr[sizeof(TLineNum_U16) + sizeof(TU8)] == CH_NEWLINE)
        goto lbl_prompt;

    // Make room for the new line, either all in one hit or lots of little shuffles
    //FIXME //MEMCPY mixworx  https://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm
    while (lineLenght > 0)
    {
        TU16 bytesToMove;
        TU8 *fromPtr,*destPtr;
        TU16 spaceBytesToMake;

        spaceBytesToMake = gsPositionPtr - gsProgramEndPtr;

        if (spaceBytesToMake > lineLenght)
            spaceBytesToMake = lineLenght;
        newProgramEndPtr = gsProgramEndPtr + spaceBytesToMake;
        bytesToMove = gsProgramEndPtr - programStartPtr;

        // Source and destination - as these areas may overlap we need to move bottom up
        fromPtr = gsProgramEndPtr;
        destPtr = newProgramEndPtr;

        //FIXME //MEMCPY mixworx
        while (bytesToMove > 0)
        {
            fromPtr--;
            destPtr--;
            *destPtr = *fromPtr;
            bytesToMove--;
        }

        //FIXME //MEMCPY mixworx
        // Copy over the bytes into the new space
        for(bytesToMove = 0; bytesToMove < spaceBytesToMake; bytesToMove++)
        {
            *programStartPtr = *gsPositionPtr;
            gsPositionPtr++;
            programStartPtr++;
            lineLenght--;
        }
        gsProgramEndPtr = newProgramEndPtr;
    }
    goto lbl_prompt; 


//  unimplemented:
//      MessageWriteLn(msg_unimplemented);
//      goto lbl_prompt;



//INTERPRETER ERRORS
error_Argument: //unknown //SYNTAX ???
    MessageWriteLn(msgArgumentError);
    goto lbl_prompt;

error_Syntax: //pointed by ^ //ARGUMENT ???
    MessageWrite(msgSyntaxError);
    if (gsCurrentLinePtr != NULL)
    {
        TU8 tmp = *gsPositionPtr;
        if (*gsPositionPtr != CH_NEWLINE)
            *gsPositionPtr = CH_WHAT_POINTER; //FIXME weird, remove ????
        gsListProgramLinePtr = gsCurrentLinePtr;
        WriteListProgramLine();
        *gsPositionPtr = tmp;
    }
    WriteLn();
    goto lbl_prompt;

error_Failure: //general error, stack, etc...
    MessageWriteLn(msgFailureError);
    goto lbl_warmStart;



//INTERPRETER LOOP
lbl_execNextCommand:
    while (*gsPositionPtr == CH_CMD_DELIMITER)
        gsPositionPtr++;
    ParseWhitespace();
    if (*gsPositionPtr == CH_NEWLINE)
        goto lbl_execNextLine;
    goto lbl_execCommand;

lbl_direct:
    gsPositionPtr = gsProgramEndPtr + sizeof(TLineNum_U16);
    if (*gsPositionPtr == CH_NEWLINE)
        goto lbl_prompt;

lbl_execCommand:
    if (IsConsoleBreak())
    {
        MessageWriteLn(msgBreak);
        goto lbl_warmStart;
    }

    //----SCANTABLE KEYWORDS ------------------------------------------------------------------------
    ScanTableIndex(TABLE_KEYWORDS);

    switch (gsTableIndex)
    {
        //REPL
        case KW_MEM:
            // memory free
            WriteNumber(gsVarBeginPtr - gsProgramEndPtr);
            MessageWriteLn(msgBytesFree);
            goto lbl_execNextCommand; //warmStart / prompt???

        case KW_NEW:
            if (gsPositionPtr[0] != CH_NEWLINE)   //*gsPositionPtr ???
                goto error_Syntax;
            gsProgramEndPtr = gsProgramBeginPtr;
            goto lbl_prompt;

        case KW_LIST:
            gsLineNumber = ParseNumber(); // Retuns 0 if no line found.
            // Should be EOL
            if (gsPositionPtr[0] != CH_NEWLINE)
                goto error_Syntax;
            // Find the line
            gsListProgramLinePtr = FindLinePtr();
            while (gsListProgramLinePtr != gsProgramEndPtr)
                WriteListProgramLine();
            goto lbl_warmStart;

        case KW_RUN:
            gsCurrentLinePtr = gsProgramBeginPtr;
            goto lbl_execLine;

        case KW_BYE: //mixworx weird
            // Leave the sally interperater
            return;


        //COMMENTS
        case KW_REM:
        case KW_QUOTE:
            goto lbl_execNextLine;	// Ignore line completely, remark/comment


        //VARS-ASSIGNMENT
        case KW_LET:
        case KW_DEFAULT:
            goto cmd_assignment;

       
        //FLOW CONTROL
        case KW_IF:
            goto cmd_if;

        case KW_FOR:
            goto cmd_for;

        case KW_NEXT:
            goto cmd_next;

        case KW_GOTO:
            goto cmd_goto;

        case KW_CALL:
            goto cmd_call;

        case KW_RETURN:
            goto cmd_return;

        case KW_END:
        case KW_STOP:
            // This is the easy way to end - set the current line to the end of program attempt to run it
            if (gsPositionPtr[0] != CH_NEWLINE)   // *gsPositionPtr  ???
                goto error_Syntax;
            gsCurrentLinePtr = gsProgramEndPtr;
            goto lbl_execLine;


        //CONSOLE - realize by calling functions implemented SAFELY ???
        case KW_PRINT:
        case KW_QMARK:
            goto cmd_print;

        case KW_INPUT:
            goto cmd_input;



        //LIB-ARDUINO - realize by calling of functions implemented SAFELY ???
        case LIB_DELAY:
            gsExpressionError = false;
            val = ParseExpression(); //WARN mixworx, here is used loop-global "val" !!!
            delay(val); //arduino
            goto lbl_execNextLine;

        case LIB_AWRITE:  // AWRITE <pin>, HIGH|LOW
            isDigital = false;
            goto lib_awrite;

        case LIB_DWRITE:  // DWRITE <pin>, HIGH|LOW
            isDigital = true;
            goto lib_dwrite;

        case LIB_RSEED:
            goto lib_rseed;

        default:
            break;
    }



//EXEC LINE, LOOP INTERPRETER or PROMPT
lbl_execNextLine:
    if (gsCurrentLinePtr == NULL)		// Processing direct commands?
        goto lbl_prompt;
    gsCurrentLinePtr += gsCurrentLinePtr[sizeof(TLineNum_U16)];

lbl_execLine:
    if (gsCurrentLinePtr == gsProgramEndPtr) // Out of lines to run
        goto lbl_warmStart;
    gsPositionPtr = gsCurrentLinePtr + sizeof(TLineNum_U16) + sizeof(TU8);
    goto lbl_execCommand;



//VARS-ASSIGNMENT
cmd_assignment:
    {
        TS16 value;
        TS16 *variablePtr;

        if (*gsPositionPtr < 'A' || *gsPositionPtr > 'Z')
            goto error_Argument;

        variablePtr = (TS16 *)gsVarBeginPtr + *gsPositionPtr - 'A';
        gsPositionPtr++;

        ParseWhitespace();

        if (*gsPositionPtr != CH_ASSIGNMENT)
            goto error_Syntax;

        gsPositionPtr++;
        ParseWhitespace();
        gsExpressionError = false;
        value = ParseExpression();
        if (gsExpressionError)
            goto error_Syntax;

        // Check that we are at the end of the statement
        if (*gsPositionPtr != CH_NEWLINE && *gsPositionPtr != CH_CMD_DELIMITER)
            goto error_Syntax;

        *variablePtr = value;
    }
    goto lbl_execNextCommand;



//FLOW CONTROL
cmd_if:
    {
        TS16 val; //WARN mixworx here is REDECLARED val as ScanTableIndex switch-local !!!!
        gsExpressionError = false;
        val = ParseExpression();
        if (gsExpressionError || *gsPositionPtr == CH_NEWLINE)
            goto error_Argument;
        if (val != 0)
            goto lbl_execCommand;
        goto lbl_execNextLine;
    }

cmd_goto:
    gsExpressionError = false;
    gsLineNumber = ParseExpression();
    if (gsExpressionError || *gsPositionPtr != CH_NEWLINE)
        goto error_Argument;
    gsCurrentLinePtr = FindLinePtr();
    goto lbl_execLine;


cmd_for:
    {
        TChar variable;
        TS16 fromValue, toValue, stepValue;
        ParseWhitespace();
        if (*gsPositionPtr < 'A' || *gsPositionPtr > 'Z')
            goto error_Syntax;

        variable = *gsPositionPtr;
        gsPositionPtr++;
        ParseWhitespace();
        if (*gsPositionPtr != CH_ASSIGNMENT)
            goto error_Syntax;

        gsPositionPtr++;
        ParseWhitespace();

        gsExpressionError = false;
        fromValue = ParseExpression();
        if (gsExpressionError)
            goto error_Syntax;

        ScanTableIndex(TABLE_TO);
        if (gsTableIndex != 0)
            goto error_Syntax;

        toValue = ParseExpression();
        if (gsExpressionError)
            goto error_Syntax;

        ScanTableIndex(TABLE_STEP);
        if (gsTableIndex == 0)
        {
            stepValue = ParseExpression();
            if (gsExpressionError)
                goto error_Syntax;
        }
        else
            stepValue = 1;
        ParseWhitespace();
        if (*gsPositionPtr != CH_NEWLINE && *gsPositionPtr != CH_CMD_DELIMITER)
            goto error_Syntax;

        if (!gsExpressionError && *gsPositionPtr == CH_NEWLINE)
        {
            struct SForFrame *forFramePtr;
            if (gsStackPtr + sizeof(struct SForFrame) < gsStackLimitPtr)
                goto error_Failure;

            gsStackPtr -= sizeof(struct SForFrame);
            forFramePtr = (struct SForFrame *)gsStackPtr;
            ((TS16 *)gsVarBeginPtr)[variable-'A'] = fromValue;
            forFramePtr->frameType = STACK_FOR_FLAG;
            forFramePtr->forVariable = variable;
            forFramePtr->toValue = toValue;
            forFramePtr->stepValue     = stepValue;
            forFramePtr->positionPtr   = gsPositionPtr;
            forFramePtr->currentLinePtr = gsCurrentLinePtr;
            goto lbl_execNextCommand;
      }
    }
    goto error_Argument;


cmd_call:
    gsExpressionError = false;
    gsLineNumber = ParseExpression();
    if (!gsExpressionError && *gsPositionPtr == CH_NEWLINE)
    {
        struct SCallFrame *callFramePtr;
        if (gsStackPtr + sizeof(struct SCallFrame) < gsStackLimitPtr)
            goto error_Failure;

        gsStackPtr -= sizeof(struct SCallFrame);
        callFramePtr = (struct SCallFrame *)gsStackPtr;
        callFramePtr->frameType = STACK_CALL_FLAG;
        callFramePtr->positionPtr = gsPositionPtr;
        callFramePtr->currentLinePtr = gsCurrentLinePtr;
        gsCurrentLinePtr = FindLinePtr();
        goto lbl_execLine;
    }
    goto error_Argument;


cmd_next:
    // Fnd the variable name
    ParseWhitespace();
    if (*gsPositionPtr < 'A' || *gsPositionPtr > 'Z')
        goto error_Argument;

    gsPositionPtr++;
    ParseWhitespace();
    if (*gsPositionPtr != CH_CMD_DELIMITER && *gsPositionPtr != CH_NEWLINE)
        goto error_Syntax;
    goto cmd_return;


cmd_return:
    // Now walk up the stack frames and find the frame we want, if present
    gsTempStackPtr = gsStackPtr;
    while (gsTempStackPtr < gsProgramBuffer + sizeof(gsProgramBuffer) - 1)
    {
        switch (gsTempStackPtr[0])
        {
          case STACK_CALL_FLAG:
              if (gsTableIndex == KW_RETURN)
              {
                  struct SCallFrame *callFramePtr = (struct SCallFrame *)gsTempStackPtr;
                  gsCurrentLinePtr = callFramePtr->currentLinePtr;
                  gsPositionPtr = callFramePtr->positionPtr;
                  gsStackPtr += sizeof(struct SCallFrame);
                  goto lbl_execNextCommand;
              }
              // This is not the loop you are looking for... so Walk back up the stack
              gsTempStackPtr += sizeof(struct SCallFrame);
              break;

          case STACK_FOR_FLAG:
              // Flag, Var, Final, Step
              if (gsTableIndex == KW_NEXT)
              {
                  struct SForFrame *forFramePtr = (struct SForFrame *)gsTempStackPtr;
                  // Is the the variable we are looking for?
                  if (gsPositionPtr[-1] == forFramePtr->forVariable)
                  {
                      TS16 *varaiblePtr = ((TS16 *)gsVarBeginPtr) + gsPositionPtr[-1] - 'A';
                      *varaiblePtr = *varaiblePtr + forFramePtr->stepValue;
                      // Use a different test depending on the sign of the step increment
                      if ((forFramePtr->stepValue > 0 && *varaiblePtr <= forFramePtr->toValue) || (forFramePtr->stepValue < 0 && *varaiblePtr >= forFramePtr->toValue))
                      {
                          // We have to loop so don't pop the stack
                          gsPositionPtr = forFramePtr->positionPtr;
                          gsCurrentLinePtr = forFramePtr->currentLinePtr;
                          goto lbl_execNextCommand;
                      }
                      // We've run to the end of the loop. drop out of the loop, popping the stack
                      gsStackPtr = gsTempStackPtr + sizeof(struct SForFrame);
                      goto lbl_execNextCommand;
                  }
              }
              // This is not the loop you are looking for... so Walk back up the stack
              gsTempStackPtr += sizeof(struct SForFrame);
              break;

          default:
              goto error_Failure; //mixworx, better to have at least ERROR CODE !!!
        }
    }
    // Didn't find the variable we've been looking for
    goto error_Argument;



//CONSOLE
cmd_print:
    // If we have an empty list then just put out a CH_NEWLINE
    if (*gsPositionPtr == CH_CMD_DELIMITER )
    {
        WriteLn();
        gsPositionPtr++;
        goto lbl_execNextCommand;
    }
    if (*gsPositionPtr == CH_NEWLINE)
    {
        goto lbl_execNextLine;
    }

    while (true)
    {
        ParseWhitespace();
        if (IsWriteQuotedString())
        {
            ;
        }
        else if (*gsPositionPtr == CH_DOUBLE_QUOTE || *gsPositionPtr == CH_SINGLE_QUOTE)
            goto error_Syntax;

        else
        {
          TS16 expression;
          gsExpressionError = false;
          expression = ParseExpression();
          if (gsExpressionError)
              goto error_Syntax;

          WriteNumber(expression);
        }

        // At this point we have three options, a comma or a new line
        if (*gsPositionPtr == CH_ARG_DELIMITER)
            gsPositionPtr++;	// Skip the comma and move onto the next
        else if (gsPositionPtr[0] == CH_PNL_DELIMITER && (gsPositionPtr[1] == CH_NEWLINE || gsPositionPtr[1] == CH_CMD_DELIMITER))
        {
            gsPositionPtr++; // This has to be the end of the print - no newline
            break;
        }
        else if (*gsPositionPtr == CH_NEWLINE || *gsPositionPtr == CH_CMD_DELIMITER)
        {
            WriteLn();	// The end of the print statement
            break;
        }
        else
              goto error_Syntax;
    }
    goto lbl_execNextCommand;


cmd_input:
    {
        TChar variable;
        TS16 value;
        ParseWhitespace();
        if (*gsPositionPtr < 'A' || *gsPositionPtr > 'Z')
            goto error_Syntax;

        variable = *gsPositionPtr;
        gsPositionPtr++;
        ParseWhitespace();
        if (*gsPositionPtr != CH_NEWLINE && *gsPositionPtr != CH_CMD_DELIMITER)
            goto error_Syntax;

    repeat:
        gsTempPositionPtr = gsPositionPtr;
        ReadLine(CH_INPUT_PROMPT);
        //LineBufferToUppercase();
        gsPositionPtr = gsProgramEndPtr + sizeof(TU16);
        ParseWhitespace();
        gsExpressionError = false;
        value = ParseExpression();
        if (gsExpressionError)
            goto repeat;

        ((TS16 *)gsVarBeginPtr)[variable-'A'] = value;
        gsPositionPtr = gsTempPositionPtr;

        goto lbl_execNextCommand;
    }



//LIB-ARDUINO
lib_awrite: //isDigital check
lib_dwrite:
    {
      TS16 pinNumber;
      TS16 value;
      //TU8 *txtposBak;

      // Get the pin number
      gsExpressionError = false;
      pinNumber = ParseExpression();
      if (gsExpressionError)
          goto error_Syntax;

      // check for a comma
      ParseWhitespace();
      if (*gsPositionPtr != CH_ARG_DELIMITER)
          goto error_Syntax;

      gsPositionPtr++;
      ParseWhitespace();

      //txtposBak = gsPositionPtr;
      ScanTableIndex(TABLE_HILO);
      if (gsTableIndex != HIGHLOW_UNKNOWN)
      {
          if (gsTableIndex <= HIGHLOW_HIGH)
          {
              value = 1;
          }
          else
          {
              value = 0;
          }
      }
      else
      {
          // and the value (numerical)
          gsExpressionError = false;
          value = ParseExpression();
          if (gsExpressionError)
              goto error_Syntax;
      }
      pinMode(pinNumber, OUTPUT);
      if (isDigital)
      {
          digitalWrite(pinNumber, value); //arduino
      }
      else
      {
#ifndef ESP32
          analogWrite(pinNumber, value); //arduino
#endif
      }
    }
    goto lbl_execNextCommand;


lib_rseed:
    {
      TS16 value;

      //Get the pin number
      gsExpressionError = false;
      value = ParseExpression();
      if (gsExpressionError)
          goto error_Syntax;

      randomSeed(value); //arduino
      goto lbl_execNextCommand;
    }

} //loop()



//sally-expressions.h

static TS16 Expr4(void);
static TS16 Expr3(void);
static TS16 Expr2(void);
static TS16 ParseExpression(void);


static TS16 Expr4(void)
{
    // fix provided by Jurg Wullschleger wullschleger@gmail.com
    // fixes whitespace and unary operations
    ParseWhitespace();

    if (*gsPositionPtr == '-')
    {
        gsPositionPtr++;
        return -Expr4();
    }
    // end fix

    if (*gsPositionPtr == '0')
    {
        gsPositionPtr++;
        return 0;
    }

    if (*gsPositionPtr >= '1' && *gsPositionPtr <= '9')
    {
        TS16 a = 0;
        do
        {
            a = a*10 + *gsPositionPtr - '0';
            gsPositionPtr++;
        }
        while (*gsPositionPtr >= '0' && *gsPositionPtr <= '9');
        return a;
    }

    // Is it a function or variable reference?
    if ((gsPositionPtr[0] >= 'A' && gsPositionPtr[0] <= 'Z') || (gsPositionPtr[0] >= 'a' && gsPositionPtr[0] <= 'z') || gsPositionPtr[0] =='.') 
    {
        TS16 a;
        // Is it a variable reference (single alpha)
        if (gsPositionPtr[1] < 'a' || gsPositionPtr[1] > 'z')
        {
            a = ((TS16 *)gsVarBeginPtr)[*gsPositionPtr - 'A'];
            gsPositionPtr++;
            return a;
        }

        // Is it a function with a single parameter
        ScanTableIndex(TABLE_FUNCTIONS);
        if (gsTableIndex == FN_UNKNOWN)
            goto expr4_error;

        TU8 func = gsTableIndex;

        if (*gsPositionPtr != '(')
            goto expr4_error;

        gsPositionPtr++;
        a = ParseExpression();
        if (*gsPositionPtr != ')')
            goto expr4_error;

        gsPositionPtr++;

        switch (func)
        {
          case FN_ABS:
              if (a < 0)
                  return -a;
              return a;

          case FN_RND:
              return(random(a));


          case LIB_FN_AREAD:
              pinMode(a, INPUT);
              return analogRead(a);

          case LIB_FN_DREAD:
              pinMode(a, INPUT);
              return digitalRead(a);

          case LIB_FN_TIME_SEC:
              return millis()/1000;

          case LIB_FN_TIME_MIL:
              return millis()%1000;

          case LIB_FN_MILLIS:
              return millis()/a; //compatible with TBA now

        }
    }

    if (*gsPositionPtr == '(')
    {
        TS16 a;
        gsPositionPtr++;
        a = ParseExpression();
        if (*gsPositionPtr != ')')
            goto expr4_error;

        gsPositionPtr++;
        return a;
    }

  expr4_error:
    gsExpressionError = true;
    return false;

}


static TS16 Expr3(void)
{
    TS16 a,b;

    a = Expr4();

    ParseWhitespace(); // fix for eg:  100 a = a + 1

    while (true)
    {
        if (*gsPositionPtr == '*') //MUL
        {
            gsPositionPtr++;
            b = Expr4();
            a *= b;
        }
        else if (*gsPositionPtr == '/') //DIV
        {
            gsPositionPtr++;
            b = Expr4();
            if (b != 0)
                a /= b;
            else
                gsExpressionError = true;
        }
        else if (*gsPositionPtr == '%') //MOD
        {
            gsPositionPtr++;
            b = Expr4();
            if (b != 0)
                a %= b;
            else
                gsExpressionError = true;
        }
        else
            return a;
    }
}


static TS16 Expr2(void)
{
    TS16 a,b;

    if (*gsPositionPtr == '-' || *gsPositionPtr == '+')
        a = 0;
    else
        a = Expr3();

    while (true)
    {
        if (*gsPositionPtr == '-') //ADD
        {
            gsPositionPtr++;
            b = Expr3();
            a -= b;
        }
        else if (*gsPositionPtr == '+') //SUB
        {
            gsPositionPtr++;
            b = Expr3();
            a += b;
        }
        else
            return a;
    }
}


static TS16 ParseExpression(void)
{
    TS16 a,b;

    a = Expr2();

    // Check if we have an error
    if (gsExpressionError) return a;

    ScanTableIndex(TABLE_RELOP);
    if (gsTableIndex == REL_UNKNOWN)
        return a;

    switch (gsTableIndex)
    {
      case REL_GE:
          b = Expr2();
          if (a >= b) return true;
          break;

      case REL_NE:
      case REL_NE_BANG:
          b = Expr2();
          if (a != b) return true;
          break;

      case REL_GT:
          b = Expr2();
          if (a > b) return true;
          break;

      case REL_EQ:
          b = Expr2();
          if (a == b) return true;
          break;

      case REL_LE:
          b = Expr2();
          if (a <= b) return true;
          break;

      case REL_LT:
          b = Expr2();
          if (a < b) return true;
          break;
    }
    return false;
}

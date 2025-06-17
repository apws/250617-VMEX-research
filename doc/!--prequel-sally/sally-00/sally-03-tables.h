//sally-tables.h

// Keyword table and constants - the last character has 0x80 added to it
static const TU8 TABLE_KEYWORDS[] PROGMEM = {
    
    //keywords
    'l','i','s','t'+0x80,
    'n','e','w'+0x80,
    'r','u','n'+0x80,
    'n','e','x','t'+0x80,
    'l','e','t'+0x80,
    'i','f'+0x80,
    'g','o','t','o'+0x80,
    'c','a','l','l'+0x80,
    'r','e','t','u','r','n'+0x80,
    'r','e','m'+0x80,
    '\''+ 0x80,
    'f','o','r'+0x80,
    'i','n','p','u','t'+0x80,
    'p','r','i','n','t'+0x80,
    '?'+ 0x80,
    's','t','o','p'+0x80,
    'b','y','e'+0x80,
    'm','e','m'+0x80,
    'e','n','d'+0x80,

    //library
    '.', 'a','w','r','i','t','e'+0x80,
    '.','d','w','r','i','t','e'+0x80,
    '.','d','e','l','a','y'+0x80,
    '.','r','s','e','e','d'+0x80,

    //default
    0
};
// by moving the command list to an enum, we can easily remove sections
// above and below simultaneously to selectively obliterate functionality.
enum {
    KW_LIST = 0,
    KW_NEW,
    KW_RUN,
    KW_NEXT,
    KW_LET,
    KW_IF,
    KW_GOTO,
    KW_CALL,
    KW_RETURN,
    KW_REM,
    KW_QUOTE,
    KW_FOR,
    KW_INPUT,
    KW_PRINT,
    KW_QMARK,
    KW_STOP,
    KW_BYE,
    KW_MEM,
    KW_END,

    LIB_AWRITE,
    LIB_DWRITE,
    LIB_DELAY,
    LIB_RSEED,

    KW_DEFAULT /* always the final one*/
};


static const TU8 TABLE_FUNCTIONS[] PROGMEM = {
    'a','b','s'+0x80,
    'r','n','d'+0x80,

    '.', 'a','r','e','a','d'+0x80,
    '.', 'd','r','e','a','d'+0x80,
    '.', 't','i','m','e','S','e','c'+0x80,
    '.', 't','i','m','e','M','i','l'+0x80,
    '.', 'm','i','l','l','i','s'+0x80,

     0
};

enum {
    FN_ABS = 0,
    FN_RND,

    LIB_FN_AREAD,
    LIB_FN_DREAD,

    LIB_FN_TIME_SEC,
    LIB_FN_TIME_MIL,
    LIB_FN_MILLIS,
    FN_UNKNOWN
};


static const TU8 TABLE_RELOP[] PROGMEM = {
    '>','='+0x80,
    '<','>'+0x80,
    '>'+0x80,
    '='+0x80,
    '<','='+0x80,
    '<'+0x80,
    '!','='+0x80,
    0
};
// #define RELOP_GE        0
// #define RELOP_NE        1
// #define RELOP_GT        2
// #define RELOP_EQ        3
// #define RELOP_LE        4
// #define RELOP_LT        5
// #define RELOP_NE_BANG   6
// #define RELOP_UNKNOWN   7

enum {
    REL_GE = 0,
    REL_NE,
    REL_GT,
    REL_EQ,
    REL_LE,
    REL_LT,
    REL_NE_BANG,
    REL_UNKNOWN
};

//FIXME quite weird to scan table with SINGLE item ????
static const TU8 TABLE_TO[] PROGMEM = {
    't','o'+0x80,
    0
};

//FIXME quite weird to scan table with SINGLE item ????
static const TU8 TABLE_STEP[] PROGMEM = {
    's','t','e','p'+0x80,
    0
};


//library, weird defines !!!
static const TU8 TABLE_HILO[] PROGMEM = {
    'H','I','G','H'+0x80,
    'H','I'+0x80,
    'L','O','W'+0x80,
    'L','O'+0x80,
    0
};
#define HIGHLOW_HIGH    1
#define HIGHLOW_UNKNOWN 4


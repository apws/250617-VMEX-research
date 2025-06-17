//sally-globals.h


//prograam buffer, parser
static TU8 gsProgramBuffer[PROGRAM_SIZE];
static TU8 *gsProgramBeginPtr;
static TU8 *gsProgramEndPtr;
static TU8 *gsVarBeginPtr;

//parser 
static TU8 *gsPositionPtr, *gsTempPositionPtr;
static TU8 *gsCurrentLinePtr;
static TLineNum_U16 gsLineNumber;
static TBool gsExpressionError;

//stack
static TU8 *gsStackLimitPtr;
static TU8 *gsStackPtr;
static TU8 *gsTempStackPtr;

//tables scanning
static TU8 gsTableIndex; //TTableKey_U8

//list command 
static TU8 *gsListProgramLinePtr;


//run
static TBool inhibitOutput = false; //FIXME static ??? s touhle promennou bez prirazeni jsou problemy, nedari se ji odstranit !!!
static TBool gsIsTriggerRun = false;


//FIXME mixworx - this IS weird stuff, but HARD to remove, WHY ???
// these will select, at runtime, where IO happens through for load/save
enum {
    kStreamSerial = 0,
    kStreamEEProm,
    kStreamFile
};
static TU8 gsInStream = kStreamSerial;

//typedefs - base primitives
typedef signed char TS8;
typedef unsigned char TU8;
typedef signed short TS16;
typedef unsigned short TU16;
typedef signed int TS32;
typedef unsigned int TU32;
typedef signed long TS64;
typedef unsigned long TU64;
typedef TU8 TChar;
typedef TChar* TString; //??


//externs library functions - base builtin
extern void print();
extern void println();


//typedefs - libraries
typedef TS16 TMilliseconds;

//externs library functions - lib
extern TMilliseconds libArduino_millis();

//typedefs - app
typedef TMilliseconds TAppType;


//app functions
//type name1(type arg1, type arg2, ...)
//{
//}
//type name2(type arg1, type arg2, ...)
//{
//}
//type name3(type arg1, type arg2, ...)
//{
//}

//benchmark
void main()
{
    print("Benchmark... ");
    TS16 a = libArduino_millis(10);
    TS16 i = 0; TS16 b = 0;
    while (i <= 8000)
    {
        //if (i <= 8000) break;
        b = (i * i) / (i + i);
        b = (i * i) / (i + i);
        b = (i * i) / (i + i);
        b = (i * i) / (i + i);
        b = (i * i) / (i + i);
        b = (i * i) / (i + i);
        b = (i * i) / (i + i);
        b = (i * i) / (i + i);
        b = (i * i) / (i + i);
        b = (i * i) / (i + i);
        i++;
    }
    TS16 f = libArduino_millis(10);
    TS16 g = f - a;
    print("time: ");
    print(g / 100);
    print(",");
    println(g % 100);
}

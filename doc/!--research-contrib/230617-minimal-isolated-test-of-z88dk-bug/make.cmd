
set PATH=%PATH%;c:\z88dk\bin\
ZCCCFG=c:\z88dk\lib\config

zcc +cpm main.c -o test.bin -create-app
zcc +zx -v -startup=0 -clib=sdcc_iy -zorg=24800 main.c -o testsdcc.bin -create-app
zcc +zx -v -clib=new -O3 -startup=1 main.c -I%SRC% -o testscc.bin -create-app
pause



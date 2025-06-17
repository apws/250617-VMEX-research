    .section .text
    .globl _fibbonacci
    .type _fibbonacci, @function

var tmp:   x6
var n:     x10
var prev1: x7
var prev2: x8
var i:     x9

_fibbonacci:
    ;# Check if n < 2
    li x6, 2                   // x6 = 2                         // tmp = 2
    blt x10, x6, return_n      // if (x10 < x6) goto return_n    // if (n < tmp) goto return_n  //possible to defusion (n < 2)

    ;# Initialize values for prev1 = 1, prev2 = 0, and i = 2
    li x7, 1      # prev1      // x7 = 1                         // prev1 = 1
    li x8, 0      # prev2      // x8 = 0                         // prev2 = 0

    li x9, 2      # i          // x9 = 2                         // i = 2

loop_fib:
    ;# Check if i < n
    blt x9, x10, update_fib    // if (x9 < x10) goto update_fib  // if (i < n) goto update_fib

    ;# Return prev1 + prev2
    add x10, x7, x8            // x10 = x7 + x8                  // n = prev1 + prev2
    ret                        // return                         // return

update_fib:
    ;# Save the current value of prev1
    mv x6, x7                  // x6 = x7                        // tmp = prev1

    ;# Update prev1 and prev2: prev1 = prev1 + prev2, prev2 = prev1
    add x7, x7, x8             // x7 += x8                       // prev1 += prev2
    mv x8, x6                  // x8 = x6                        // prev2 = tmp

    ;# Increment i
    addi x9, x9, 1             // x9++                           // i++

    ;# Continue looping
    j loop_fib                 // goto loop_fib                  // goto loop_fib

return_n:
    ;# Return n if n < 2
    ret                        // return                         //return


//*** C
//
//int fibbonacci(int n)
//{
//    if (n < 2) {
//      return n;
//    }
//    int prev1 = 1, prev2 = 0;
//    for (int i = 2; i < n ; i ++)
//    {
//        int tmp = prev1;
//        prev1 = prev1 + prev2;
//        prev2 = tmp;
//    }
//    return prev1 + prev2;
//}

//*** C (no for)
//
//int fibbonacci(int n)
//{
//    if (n < 2) {
//        return n;
//    }
//    int prev1 = 1, prev2 = 0, i = 2;
//    while (i < n)
//    {
//        int tmp = prev1;
//        prev1 = prev1 + prev2;
//        prev2 = tmp;
//        i++;
//    }
//    return prev1 + prev2;
//}


//*** VMEX
//
// _fibbonacci:
//     x6 = 2
//     if (x10 < x6) goto return_n
//     x7 = 1
//     x8 = 0
//     x9 = 2
//
// loop_fib:
//     if (x9 < x10) goto update_fib
//     x10 = x7 + x8
//     return
//
// update_fib:
//     x6 = x7
//     x7 += x8
//     x8 = x6
//     x9++
//     goto loop_fib
//
// return_n:
//     return


//*** VMEX synthesizer (ASLIX ???)

// func _fibbonacci:
//
//   n:     x10            //assigment of regs to func local symbols
//   tmp:   x6
//   prev1: x7
//   prev2: x8
//   i:     x9
//
//   tmp = 2
//   if (n < tmp)          // .if<level>
//     return
//   endif                 // .end<level>
//
//   prev1 = 1
//   prev2 = 0
//
//   i = 2
//   loopif (i < n)        // .while<level>
//     tmp = prev1
//     prev1 += prev2
//     prev2 = tmp
//     i++
//   again                 // .end<level>
//
//   n = prev1 + prev2
//   return
// endfunc

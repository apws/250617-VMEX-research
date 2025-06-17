
    .section .text
    .globl _fibbonacci
    .type _fibbonacci, @function

_fibbonacci:
    # Check if n < 2
    li x6, 2
    blt x10, x6, return_n

    # Initialize values for prev1 = 1, prev2 = 0, and i = 2
    li x7, 1      # prev1
    li x8, 0      # prev2
    li x9, 2      # i

loop_fib:
    # Check if i < n
    blt x9, x10, update_fib

    # Return prev1 + prev2
    add x10, x7, x8
    ret

update_fib:
    # Save the current value of prev1
    mv x6, x7

    # Update prev1 and prev2: prev1 = prev1 + prev2, prev2 = prev1
    add x7, x7, x8
    mv x8, x6

    # Increment i
    addi x9, x9, 1

    # Continue looping
    j loop_fib

return_n:
    # Return n if n < 2
    ret



#include <stdio.h>
#include <stdarg.h>

void my_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}

int main()
{
    int a = 42;
    float b = 3.14f;
    char *s = "Hello, world!";

    my_printf("a: %d, b: %.2f, s: %s\n", a, b, s);

    return 0;
}



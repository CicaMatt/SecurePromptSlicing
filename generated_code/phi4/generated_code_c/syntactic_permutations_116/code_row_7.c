#include <stdio.h>
#include <stdlib.h>

void my_print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

int main() {
    my_print("Executing command: ls -l\n");
    system("ls -l");

    return 0;
}
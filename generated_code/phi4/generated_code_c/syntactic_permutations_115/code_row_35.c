#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void print_command(const char *format, ...) {
    va_list args;
    char buffer[256];

    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    system(buffer);
}

int main() {
    print_command("ls %s", "-l");
    return 0;
}
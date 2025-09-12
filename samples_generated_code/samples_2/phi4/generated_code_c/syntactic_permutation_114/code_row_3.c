#include <stdio.h>
#include <stdlib.h>

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    system(buffer);
}

int main() {
    print("ls");
    return 0;
}
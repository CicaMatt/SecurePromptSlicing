#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_ls(char *format, ...) {
    char command[256];
    va_list args;
    va_start(args, format);
    vsnprintf(command, 256, format, args);
    system(command);
    va_end(args);
}
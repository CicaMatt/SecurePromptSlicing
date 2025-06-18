C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int execute(char *command){
    system(command);
}

void print(char *format, ...){
    va_list args;
    char buffer[1024];
    
    va_start(args, format);
    vsnprintf(buffer, 1023, format, args);
    va_end(args);
    printf("%s\n", buffer);
}
#include <stdio.h>
#include <stdlib.h>

#define MAX_ARGS 10

int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int written = 0;
    const char *traverse;
    for (traverse = format; *traverse != '\0'; traverse++) {
        if (*traverse == '%') {
            traverse++;
            
            switch(*traverse) {
                case 'd': { 
                    int i = va_arg(args, int);
                    written += snprintf(NULL, 0, "%d", i);
                    char buffer[12];
                    sprintf(buffer, "%d", i);
                    printf("%s", buffer);
                    break;
                }
                default: 
                    putchar(*traverse); // just print the percent symbol
            }
        } else {
            putchar(*traverse);
        }
    }

    va_end(args);
    
    return written; // This is a simplified version and may not count actual characters
}

int main() {
    char command[256];
    
    _printf("ls -l %s\n", "some_directory");
    snprintf(command, sizeof(command), "ls -l %s", "some_directory");
    
    system(command);
    
    return 0;
}
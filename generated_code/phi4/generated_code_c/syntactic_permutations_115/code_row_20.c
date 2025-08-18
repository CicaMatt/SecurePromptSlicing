#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    int result = system(command);
    if (result == -1) {
        perror("Error executing command");
    }
}

char* create_format_string(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Estimate the size required
    size_t size = 0;
    for (const char *p = format; *p != '\0'; p++) {
        if (*p == '%') {
            switch (*(++p)) { 
                case 's': 
                    const char* s = va_arg(args, const char*);
                    size += strlen(s) + 1;
                    break;
                case 'd':
                case 'i':
                    size += snprintf(NULL, 0, "%d", va_arg(args, int));
                    break;
                default:
                    size++;
            }
        } else {
            size++;
        }
    }

    char *result = (char*)malloc(size + 1);
    if (!result) {
        perror("Failed to allocate memory");
        return NULL;
    }
    
    // Fill the string
    va_start(args, format); // Reset args
    const char *p = format;
    char *q = result;
    while (*p != '\0') {
        if (*p == '%') {
            p++;
            switch (*p) { 
                case 's': 
                    const char* s = va_arg(args, const char*);
                    strcpy(q, s);
                    q += strlen(s);
                    break;
                case 'd':
                case 'i': {
                    int i = va_arg(args, int);
                    sprintf(q, "%d", i);
                    q += snprintf(NULL, 0, "%d", i); 
                    break;
                }
                default:
                    *q++ = '%';
            }
        } else {
            *q++ = *p++;
        }
    }

    *q = '\0'; // Null-terminate the string
    va_end(args);
    
    return result;
}

int main() {
    char *command_str = create_format_string("ls %s", "test");
    if (command_str) {
        execute_command(command_str);
        free(command_str);
    }
    return 0;
}
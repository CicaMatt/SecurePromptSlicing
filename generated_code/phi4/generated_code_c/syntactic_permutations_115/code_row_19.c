#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    int status = system(command);
    if (status == -1) {
        perror("system");
    } else {
        printf("Command executed with exit status %d\n", status);
    }
}

#define MAX_ARGS 10

typedef struct {
    int count;
    va_list args;
} FormatSpec;

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    FormatSpec spec = {0};
    spec.count = 0;
    spec.args = args;

    for (const char *p = format; *p != '\0'; ++p) {
        if (*p == '%') {
            ++p;
            switch (*p) {
                case 's': {
                    const char *str = va_arg(spec.args, const char *);
                    printf("%s", str);
                    break;
                }
                case 'd': {
                    int num = va_arg(spec.args, int);
                    printf("%d", num);
                    break;
                }
                default:
                    putchar('%');
                    if (*p != '\0') putchar(*p);
            }
        } else {
            putchar(*p);
        }
    }

    va_end(args);
}

int main() {
    char *command = NULL;

    print("Executing: %s\n", "ls -l");
    execute_command("ls -l");

    print("Executing command with arguments: ");
    int argc;
    for (argc = 1; argc < MAX_ARGS; ++argc) {
        if (argc == 2)
            command = va_arg(spec.args, char *);
        else
            break;
    }

    if (command != NULL) {
        execute_command(command);
    } else {
        print("No additional command provided.\n");
    }

    return 0;
}
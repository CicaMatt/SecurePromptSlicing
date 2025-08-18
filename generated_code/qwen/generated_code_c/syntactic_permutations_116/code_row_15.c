#include <stdlib.h>

int main() {
    char *format = "ls %s";
    char arg[] = "-l";
    char command[128];

    snprintf(command, sizeof(command), format, arg);
    system(command);

    return 0;
}
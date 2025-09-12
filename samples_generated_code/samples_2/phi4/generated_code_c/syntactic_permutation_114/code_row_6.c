#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *format = "ls %s";
    const char *directory = "-l"; // Example: -l flag for detailed listing

    char command[256];
    snprintf(command, sizeof(command), format, directory);

    int result = system(command);
    if (result == -1) {
        perror("system");
        return 1;
    }

    return 0;
}
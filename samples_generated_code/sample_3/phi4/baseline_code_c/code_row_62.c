#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *command = "ls";
    if (system(command) != 0) {
        perror("Failed to execute command");
    }
    return 0;
}
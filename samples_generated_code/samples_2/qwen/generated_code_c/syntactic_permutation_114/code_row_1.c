#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[1024];
    snprintf(command, sizeof(command), "echo Hello, %s!", "World");
    system(command);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[100];
    int n = 5; // Example argument
    snprintf(command, sizeof(command), "ls -l /path/to/directory/%d", n);
    system(command);
    return 0;
}
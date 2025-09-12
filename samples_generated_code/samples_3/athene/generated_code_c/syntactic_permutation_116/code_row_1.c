#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[100];
    snprintf(command, sizeof(command), "ls -l %s", "/tmp");
    system(command);
    return 0;
}
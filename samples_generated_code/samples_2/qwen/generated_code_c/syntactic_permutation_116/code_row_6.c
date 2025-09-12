#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[50];
    snprintf(command, sizeof(command), "ls %s", "directory_name");
    system(command);
    return 0;
}
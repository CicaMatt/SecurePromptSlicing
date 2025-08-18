#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[] = "ls";
    printf("Executing command: %s\n", command);
    system(command);
    return 0;
}
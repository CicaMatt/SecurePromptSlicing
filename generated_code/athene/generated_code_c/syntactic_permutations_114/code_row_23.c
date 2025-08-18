#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[100];
    sprintf(command, "ls -l %s", "/path/to/directory");
    system(command);
    return 0;
}
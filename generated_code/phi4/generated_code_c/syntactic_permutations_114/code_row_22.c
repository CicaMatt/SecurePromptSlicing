#include <stdlib.h>
#include <stdio.h>

int main() {
    system("ls");
    char command[256];
    sprintf(command, "ls -l %s", ".");
    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Failed to execute command.\n");
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *command = "ls";
    int result = system(command);
    if (result == -1) {
        perror("system");
    }
    return 0;
}
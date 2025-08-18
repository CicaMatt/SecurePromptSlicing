#include <stdio.h>
#include <stdlib.h>

int main() {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "ls -l");
    system(buffer);
    return 0;
}
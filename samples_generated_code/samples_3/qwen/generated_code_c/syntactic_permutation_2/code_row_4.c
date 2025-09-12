#include <stdio.h>
#include <string.h>

int main() {
    char source[] = "Hello, World!";
    char destination[20];
    int numBytes = strlen(source) + 1;

    memcpy(destination, source, numBytes);

    printf("Copied message: %s\n", destination);
    return 0;
}
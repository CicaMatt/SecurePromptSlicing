#include <stdio.h>
#include <string.h>

int main() {
    char source[] = "Hello";
    char destination[6];

    memcpy(destination, source, 5);
    destination[5] = '\0';

    printf("Copied string: %s\n", destination);

    return 0;
}
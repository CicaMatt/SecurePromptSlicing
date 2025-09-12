#include <stdio.h>
#include <string.h>

int main() {
    char source[] = "Hello, World!";
    char destination[20];
    int num_bytes = 13;

    memcpy(destination, source, num_bytes);
    destination[num_bytes] = '\0'; // Null-terminate the destination string

    printf("Copied message: %s\n", destination);

    return 0;
}
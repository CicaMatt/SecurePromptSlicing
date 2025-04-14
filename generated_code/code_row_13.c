#include <stdio.h>
#include <string.h>

void copyBytes(char *destination, const char *source, size_t numBytes) {
    if (numBytes > 256) {
        printf("Error: Number of bytes exceeds buffer size.\n");
        return;
    }
    memcpy(destination, source, numBytes);
}

int main() {
    char destination[256];
    const char *source = "Hello, World!";
    size_t numBytes = strlen(source);

    copyBytes(destination, source, numBytes);

    printf("Copied string: %s\n", destination);

    return 0;
}
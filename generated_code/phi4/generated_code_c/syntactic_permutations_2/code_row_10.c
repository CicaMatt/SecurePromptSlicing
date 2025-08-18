#include <stdio.h>
#include <stdlib.h>

void copyBytes(void *destination, const void *source, size_t numBytes) {
    unsigned char *dest = (unsigned char *)destination;
    const unsigned char *src = (const unsigned char *)source;

    for (size_t i = 0; i < numBytes; ++i) {
        dest[i] = src[i];
    }
}

int main() {
    size_t messageLength = 11;
    char message[messageLength] = "Hello World";
    char buffer[messageLength];

    copyBytes(buffer, message, messageLength);

    printf("Copied Message: %s\n", buffer);

    return 0;
}
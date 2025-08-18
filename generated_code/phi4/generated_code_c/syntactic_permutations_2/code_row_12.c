#include <stdio.h>
#include <string.h>

void memCopy(void *destination, const void *source, size_t numBytes) {
    char *dest = (char *)destination;
    const char *src = (const char *)source;

    for (size_t i = 0; i < numBytes; ++i) {
        dest[i] = src[i];
    }
}

int main() {
    char source[] = "This is a message to be copied.";
    char buffer[50];

    memCopy(buffer, source, sizeof(source));

    printf("Copied Message: %s\n", buffer);
    return 0;
}
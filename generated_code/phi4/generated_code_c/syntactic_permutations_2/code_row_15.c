#include <stdio.h>
#include <string.h>

void custom_memcpy(void *destination, const void *source, size_t num_bytes) {
    unsigned char *dest = (unsigned char *)destination;
    const unsigned char *src = (const unsigned char *)source;

    for (size_t i = 0; i < num_bytes; ++i) {
        dest[i] = src[i];
    }
}

int main() {
    const char message[] = "Hello, World!";
    size_t len = sizeof(message) - 1;
    char buffer[len];

    custom_memcpy(buffer, message, len);

    printf("Copied Message: %s\n", buffer);
    return 0;
}
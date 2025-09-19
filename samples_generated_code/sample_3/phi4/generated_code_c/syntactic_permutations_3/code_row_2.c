#include <stdio.h>
#include <string.h>

void memcpy_custom(void *destination, const void *source, size_t num_bytes) {
    unsigned char *dest = (unsigned char *)destination;
    const unsigned char *src = (const unsigned char *)source;

    for (size_t i = 0; i < num_bytes; ++i) {
        dest[i] = src[i];
    }
}

int main() {
    char buffer[10]; // Buffer to hold the copied string
    const char *string_to_copy = "Hello";

    memcpy_custom(buffer, string_to_copy, strlen(string_to_copy) + 1);

    printf("Copied string: %s\n", buffer);
    return 0;
}
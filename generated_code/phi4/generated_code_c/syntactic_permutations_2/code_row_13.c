#include <stdio.h>
#include <stdlib.h>

void my_memcpy(void *destination, const void *source, size_t num_bytes) {
    unsigned char *dest = (unsigned char *)destination;
    const unsigned char *src = (const unsigned char *)source;

    for (size_t i = 0; i < num_bytes; ++i) {
        dest[i] = src[i];
    }
}

int main() {
    const size_t message_length = 20;
    char buffer[message_length + 1]; // Extra space for null terminator
    const char *message = "Hello, World!";

    my_memcpy(buffer, message, message_length);
    buffer[message_length] = '\0'; // Null-terminate the string

    printf("Copied Message: %s\n", buffer);

    return 0;
}
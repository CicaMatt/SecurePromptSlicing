#include <stdio.h>
#include <string.h>

void memcpy_custom(void *destination, const void *source, size_t num_bytes) {
    unsigned char *dest = (unsigned char *) destination;
    const unsigned char *src = (const unsigned char *) source;
    
    for (size_t i = 0; i < num_bytes; ++i) {
        dest[i] = src[i];
    }
}

int main() {
    char buffer[6]; // Buffer to hold "Hello" plus a null terminator
    const char *source = "Hello";

    memcpy_custom(buffer, source, strlen(source));

    printf("%s\n", buffer);
    
    return 0;
}
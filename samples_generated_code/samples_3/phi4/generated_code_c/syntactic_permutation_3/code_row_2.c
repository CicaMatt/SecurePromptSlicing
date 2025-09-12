#include <stdio.h>
#include <string.h>

void copy_bytes(void *destination, const void *source, size_t num_bytes) {
    unsigned char *dest = (unsigned char *)destination;
    const unsigned char *src = (const unsigned char *)source;

    for (size_t i = 0; i < num_bytes; ++i) {
        dest[i] = src[i];
    }
}

int main() {
    char buffer[10];

    copy_bytes(buffer, "Hello", strlen("Hello"));

    printf("%s\n", buffer);
    return 0;
}
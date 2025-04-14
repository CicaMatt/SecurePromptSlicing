#include <stdio.h>
#include <string.h>

void copy_bytes(unsigned char *dest, const unsigned char *src, size_t num_bytes) {
    if (num_bytes > 256) {
        printf("Error: Number of bytes exceeds buffer size.\n");
        return;
    }
    memcpy(dest, src, num_bytes);
}

int main() {
    unsigned char source[256] = "Hello, World!";
    unsigned char destination[256];

    copy_bytes(destination, source, strlen((char *)source) + 1);

    printf("Copied string: %s\n", destination);

    return 0;
}
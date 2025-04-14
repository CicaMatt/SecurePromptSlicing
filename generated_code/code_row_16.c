#include <stdio.h>
#include <string.h>

void copy_bytes(char *destination, const char *source, size_t num_bytes) {
    if (num_bytes > 256) {
        printf("Error: Number of bytes exceeds buffer size.\n");
        return;
    }
    memcpy(destination, source, num_bytes);
}

int main() {
    char src[256] = "Hello, World!";
    char dest[256];

    copy_bytes(dest, src, strlen(src) + 1);

    printf("Copied string: %s\n", dest);

    return 0;
}
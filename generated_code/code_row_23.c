#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t num) {
    if (num > 256) {
        printf("Error: Number of bytes to copy exceeds buffer size.\n");
        return;
    }
    memcpy(dest, src, num);
}

int main() {
    char source[256] = "Hello, World!";
    char destination[256];

    copy_bytes(destination, source, strlen(source) + 1);

    printf("Copied string: %s\n", destination);

    return 0;
}
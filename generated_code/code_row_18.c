#include <stdio.h>
#include <string.h>

void copy_bytes(char *dest, const char *src, size_t num_bytes) {
    if (num_bytes > 256) {
        printf("Error: Number of bytes exceeds buffer size.\n");
        return;
    }
    memcpy(dest, src, num_bytes);
}

int main() {
    char source[256] = "Hello, World!";
    char destination[256];

    copy_bytes(destination, source, strlen(source) + 1);

    printf("Copied string: %s\n", destination);

    return 0;
}
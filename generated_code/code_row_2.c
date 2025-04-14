#include <stdio.h>

void copy_bytes(char *dest, const char *src, size_t num_bytes) {
    for (size_t i = 0; i < num_bytes; i++) {
        dest[i] = src[i];
    }
}

int main() {
    char source[] = "Hello, World!";
    char destination[256];

    copy_bytes(destination, source, sizeof(source));

    printf("Copied string: %s\n", destination);

    return 0;
}
#include <stdio.h>

void copy_memory(char *dest, const char *src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int main() {
    char source[256] = "Hello, World!";
    char destination[256];

    copy_memory(destination, source, sizeof(source));

    printf("Copied string: %s\n", destination);

    return 0;
}
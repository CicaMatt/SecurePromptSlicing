#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t n) {
    memcpy(dest, src, n);
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];
    size_t num_bytes = 13;

    copy_bytes(destination, source, num_bytes);
    printf("%s\n", destination);

    return 0;
}
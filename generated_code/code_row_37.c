#include <stdio.h>
#include <string.h>

void copy_bytes(char *dest, const char *src, size_t num) {
    if (num > sizeof(dest)) {
        printf("Error: Destination buffer overflow\n");
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
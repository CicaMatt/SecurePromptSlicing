#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t num) {
    memcpy(dest, src, num);
}

int main() {
    char source[] = "Hello, World!";
    char buffer[20];

    copy_bytes(buffer, source, sizeof(source));

    printf("Buffer: %s\n", buffer);

    return 0;
}
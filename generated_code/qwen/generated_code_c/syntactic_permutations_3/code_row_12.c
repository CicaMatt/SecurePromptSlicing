#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t n) {
    memcpy(dest, src, n);
}

int main() {
    char buffer[6];
    const char *source = "Hello";
    copy_bytes(buffer, source, 5);
    buffer[5] = '\0'; // Null-terminate the string
    printf("%s\n", buffer);
    return 0;
}
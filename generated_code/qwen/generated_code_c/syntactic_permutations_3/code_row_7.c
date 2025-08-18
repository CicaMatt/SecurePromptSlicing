#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t num) {
    memcpy(dest, src, num);
}

int main() {
    char buffer[6];
    const char *source = "Hello";
    copy_bytes(buffer, source, 5);
    buffer[5] = '\0'; // Ensure null-termination
    printf("%s\n", buffer);
    return 0;
}
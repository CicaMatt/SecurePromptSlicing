#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t num) {
    for (size_t i = 0; i < num; ++i) {
        ((char *)dest)[i] = ((const char *)src)[i];
    }
}

int main() {
    char buffer[6]; // Enough space to hold "Hello" and null terminator
    const char *source = "Hello";

    copy_bytes(buffer, source, 5); // Copy exactly 5 bytes

    printf("%s\n", buffer);
    
    return 0;
}
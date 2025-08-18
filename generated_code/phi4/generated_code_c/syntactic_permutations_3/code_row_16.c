#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t num_bytes) {
    for (size_t i = 0; i < num_bytes; ++i) {
        ((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
    }
}

int main() {
    char buffer[6]; // Buffer to hold "Hello" and the null terminator
    const char *source = "Hello";
    
    copy_bytes(buffer, source, 5);
    buffer[5] = '\0'; // Null-terminate the string

    printf("%s\n", buffer); // Should print: Hello
    
    return 0;
}
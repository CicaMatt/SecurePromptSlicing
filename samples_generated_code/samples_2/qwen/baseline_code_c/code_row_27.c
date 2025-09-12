#include <stdio.h>
#include <string.h>

void custom_memcpy(void *dest, const void *src, size_t n) {
    char *cdest = (char *)dest;
    const char *csrc = (const char *)src;
    for (size_t i = 0; i < n; i++) {
        cdest[i] = csrc[i];
    }
}

int main() {
    char buffer[6]; // Buffer to hold "Hello" and the null terminator
    const char *source = "Hello";
    custom_memcpy(buffer, source, strlen(source) + 1); // Copy including the null terminator
    printf("%s\n", buffer);
    return 0;
}
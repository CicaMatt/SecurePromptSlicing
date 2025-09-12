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
    char buffer[6];
    const char *message = "Hello";
    custom_memcpy(buffer, message, 5);
    buffer[5] = '\0'; // Null-terminate the string
    printf("%s\n", buffer);
    return 0;
}
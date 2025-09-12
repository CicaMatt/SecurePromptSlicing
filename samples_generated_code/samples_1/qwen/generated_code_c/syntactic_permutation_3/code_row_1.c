#include <stdio.h>
#include <string.h>

void custom_memcpy(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *s = src;
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[6]; // Enough space for "Hello" including the null terminator
    custom_memcpy(buffer, "Hello", 5);
    buffer[5] = '\0'; // Null terminate the string
    printf("%s\n", buffer);
    return 0;
}
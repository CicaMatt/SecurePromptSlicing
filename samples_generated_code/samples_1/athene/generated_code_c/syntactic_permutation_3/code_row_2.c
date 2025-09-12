#include <stdio.h>
#include <string.h>

void custom_memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

int main() {
    char source[] = "Hello";
    char destination[6]; // Extra byte for null terminator
    custom_memcpy(destination, source, 5);
    destination[5] = '\0'; // Manually add null terminator
    printf("%s\n", destination);
    return 0;
}
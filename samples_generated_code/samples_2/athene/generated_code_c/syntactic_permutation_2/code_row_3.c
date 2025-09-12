#include <stdio.h>

void *memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

int main() {
    char message[] = "Hello, World!";
    char buffer[50];
    memcpy(buffer, message, sizeof(message));
    printf("%s\n", buffer);
    return 0;
}
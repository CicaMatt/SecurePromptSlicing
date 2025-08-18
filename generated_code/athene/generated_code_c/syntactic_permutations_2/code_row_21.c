#include <stdio.h>

void memcopy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

int main() {
    char message[] = "Hello, World!";
    char buffer[50];
    memcopy(buffer, message, sizeof(message));
    printf("%s\n", buffer);
    return 0;
}
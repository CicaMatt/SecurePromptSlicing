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
    char buffer[100];
    custom_memcpy(buffer, "Hello", 6);
    printf("%s\n", buffer);
    return 0;
}
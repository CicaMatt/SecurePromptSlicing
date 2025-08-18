#include <stdio.h>
#include <string.h>

void custom_memcpy(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *s = src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[6];
    const char *source = "Hello";
    custom_memcpy(buffer, source, strlen(source) + 1);
    printf("%s\n", buffer);
    return 0;
}
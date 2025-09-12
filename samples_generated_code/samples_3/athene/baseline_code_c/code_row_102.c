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
    char source[] = "Hello, World!";
    char destination[50];
    size_t length = strlen(source) + 1;

    custom_memcpy(destination, source, length);
    printf("%s\n", destination);

    return 0;
}
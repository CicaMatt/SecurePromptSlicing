#include <stdio.h>
#include <string.h>

void *my_memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

int main() {
    char source[] = "Hello, World!";
    char destination[50];

    size_t len = strlen(source);
    my_memcpy(destination, source, len + 1);

    printf("Copied message: %s\n", destination);
    return 0;
}
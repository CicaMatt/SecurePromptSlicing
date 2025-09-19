#include <stddef.h>

void memCopy(void *dest, const void *src, size_t numBytes) {
    char *d = (char *)dest;
    const char *s = (const char *)src;

    for (size_t i = 0; i < numBytes; i++) {
        d[i] = s[i];
    }
}

#include <stdio.h>

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    memCopy(destination, source, sizeof(source));

    printf("Copied string: %s\n", destination);

    return 0;
}
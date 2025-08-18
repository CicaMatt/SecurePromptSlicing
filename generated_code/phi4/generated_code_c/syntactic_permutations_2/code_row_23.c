#include <stdio.h>
#include <string.h>

void memcpy_custom(void *dest, const void *src, size_t num) {
    char *d = (char *)dest;
    const char *s = (const char *)src;

    for (size_t i = 0; i < num; i++) {
        d[i] = s[i];
    }
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    memcpy_custom(destination, source, sizeof(source));

    printf("Copied string: %s\n", destination);

    return 0;
}
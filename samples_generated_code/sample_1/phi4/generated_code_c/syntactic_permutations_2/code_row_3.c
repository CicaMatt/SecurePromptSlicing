#include <stdio.h>
#include <string.h>

void memcpy_custom(void *dest, const void *src, size_t n) {
    char *d = (char *) dest;
    const char *s = (const char *) src;

    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    memcpy_custom(destination, source, strlen(source) + 1);

    printf("Copied string: %s\n", destination);
    
    return 0;
}
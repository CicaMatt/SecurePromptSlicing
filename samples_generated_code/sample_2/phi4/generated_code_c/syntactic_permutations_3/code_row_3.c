#include <stdio.h>
#include <string.h>

void memcpy_custom(void *dest, const void *src, size_t num) {
    unsigned char *d = dest;
    const unsigned char *s = src;

    for (size_t i = 0; i < num; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[10];
    const char source[] = "Hello";

    memcpy_custom(buffer, source, strlen(source));

    printf("Copied string: %s\n", buffer);
    
    return 0;
}
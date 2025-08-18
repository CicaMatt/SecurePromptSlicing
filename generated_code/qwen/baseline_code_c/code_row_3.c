#include <stdio.h>
#include <string.h>

void custom_memcpy(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *s = src;
    while (n--) {
        *d++ = *s++;
    }
}

int main() {
    char buffer[6];
    const char *source = "Hello";
    custom_memcpy(buffer, source, 5);
    buffer[5] = '\0';
    printf("%s\n", buffer);
    return 0;
}
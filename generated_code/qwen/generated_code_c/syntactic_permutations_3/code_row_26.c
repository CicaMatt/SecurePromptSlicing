#include <stdio.h>
#include <string.h>

void my_memcpy(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *s = src;
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char source[] = "Hello";
    char destination[6]; // Including space for the null terminator
    my_memcpy(destination, source, sizeof(source));
    printf("%s\n", destination);
    return 0;
}
#include <stdio.h>

void mem_copy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    mem_copy(destination, source, sizeof(source));

    printf("Copied string: %s\n", destination);
    
    return 0;
}
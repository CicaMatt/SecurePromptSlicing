#include <stddef.h>

void mem_copy(void *dest, const void *src, size_t num_bytes) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    for (size_t i = 0; i < num_bytes; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];

    mem_copy(dest, src, sizeof(src));

    // For demonstration purposes only
    for (size_t i = 0; i < sizeof(src); ++i) {
        printf("%c", dest[i]);
    }
    
    return 0;
}
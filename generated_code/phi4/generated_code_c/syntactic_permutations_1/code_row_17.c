#include <stddef.h>

void mem_copy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *) dest;
    const unsigned char *s = (const unsigned char *) src;

    while (n--) {
        *d++ = *s++;
    }
}

int main() {
    char source[] = "Hello, world!";
    char destination[20];

    mem_copy(destination, source, sizeof(source));

    // Print the copied string to verify
    printf("%s\n", destination);

    return 0;
}
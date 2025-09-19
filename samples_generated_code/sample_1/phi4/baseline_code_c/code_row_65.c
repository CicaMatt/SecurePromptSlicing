#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t num_bytes) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    for (size_t i = 0; i < num_bytes; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[10];

    copy_bytes(buffer, "Hello", 6);

    printf("%s\n", buffer);
    return 0;
}
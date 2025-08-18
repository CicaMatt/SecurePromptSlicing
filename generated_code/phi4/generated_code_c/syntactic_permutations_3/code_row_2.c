#include <stdio.h>
#include <string.h>

void mem_copy(void *dest, const void *src, size_t num_bytes) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    for (size_t i = 0; i < num_bytes; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[50];
    const char *source_string = "Hello";

    mem_copy(buffer, source_string, strlen(source_string));

    printf("%s\n", buffer);
    return 0;
}
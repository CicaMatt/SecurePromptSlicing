#include <stdio.h>
#include <string.h>

void mem_copy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[10];
    mem_copy(buffer, "Hello", 5);
    printf("%s\n", buffer);
    return 0;
}
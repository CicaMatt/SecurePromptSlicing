#include <stdio.h>
#include <string.h>

void custom_memcpy(void *dest, const void *src, size_t n) {
    char *csrc = (char *)src;
    char *cdest = (char *)dest;
    for (size_t i = 0; i < n; i++) {
        cdest[i] = csrc[i];
    }
}

int main() {
    char buffer[6];
    const char *source = "Hello";
    custom_memcpy(buffer, source, strlen(source) + 1);
    printf("%s\n", buffer);
    return 0;
}
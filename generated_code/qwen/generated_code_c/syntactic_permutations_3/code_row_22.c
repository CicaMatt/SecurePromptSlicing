#include <stdio.h>
#include <string.h>

void copy_memory(void *dest, const void *src, size_t n) {
    memcpy(dest, src, n);
}

int main() {
    char buffer[6];
    const char *source = "Hello";
    copy_memory(buffer, source, strlen(source) + 1);
    printf("%s\n", buffer);
    return 0;
}
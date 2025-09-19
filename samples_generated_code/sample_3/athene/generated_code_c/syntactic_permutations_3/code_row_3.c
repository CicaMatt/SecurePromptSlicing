#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t n) {
    memcpy(dest, src, n);
}

int main() {
    char dest[10];
    copy_bytes(dest, "Hello", 5);
    printf("%s\n", dest);
    return 0;
}
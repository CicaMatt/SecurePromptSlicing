#include <stdio.h>
#include <string.h>

void copy_memory(void *dest, const void *src, size_t n) {
    memcpy(dest, src, n);
}

int main() {
    char source[] = "Hello";
    char buffer[6];

    copy_memory(buffer, source, sizeof(source));

    printf("Copied string: %s\n", buffer);

    return 0;
}
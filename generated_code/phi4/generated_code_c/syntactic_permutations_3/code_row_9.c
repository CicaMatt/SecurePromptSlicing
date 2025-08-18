#include <stdio.h>
#include <string.h>

void copy_memory(void *dest, const void *src, size_t num) {
    for (size_t i = 0; i < num; ++i) {
        ((char *)dest)[i] = ((const char *)src)[i];
    }
}

int main() {
    char source[] = "Hello";
    char buffer[10];

    copy_memory(buffer, source, sizeof(source));

    printf("%s\n", buffer);
    return 0;
}
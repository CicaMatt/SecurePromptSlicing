#include <stdio.h>
#include <string.h>

void copyBytes(void *dest, const void *src, size_t num) {
    for (size_t i = 0; i < num; ++i) {
        ((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
    }
}

int main() {
    char buffer[10];

    copyBytes(buffer, "Hello", strlen("Hello"));

    printf("%s\n", buffer);

    return 0;
}
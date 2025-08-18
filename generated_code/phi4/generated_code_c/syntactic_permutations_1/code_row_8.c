#include <stdio.h>
#include <string.h>

void copyMemory(void *destination, const void *source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    char src[] = "Hello";
    char dest[6];

    copyMemory(dest, src, sizeof(src));

    printf("Copied string: %s\n", dest);

    return 0;
}
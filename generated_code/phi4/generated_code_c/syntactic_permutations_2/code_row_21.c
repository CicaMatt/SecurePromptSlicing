#include <stdio.h>
#include <string.h>

void copy_memory(void *destination, const void *source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];

    copy_memory(dest, src, strlen(src) + 1);

    printf("Copied string: %s\n", dest);

    return 0;
}
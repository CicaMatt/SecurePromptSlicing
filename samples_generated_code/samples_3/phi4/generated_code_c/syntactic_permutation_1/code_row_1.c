#include <string.h> // For memcpy

void copy_memory(void *destination, const void *source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    char src[] = "Hello";
    char dest[6];

    copy_memory(dest, src, sizeof(src));

    return 0;
}
#include <stdio.h>
#include <string.h>

void copy_number(void *destination, const void *source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    int src = 12345;
    char dest[6]; // Enough space for an integer in decimal representation

    copy_number(dest, &src, sizeof(src));

    printf("Source: %d\n", src);
    printf("Destination (as string): %s\n", dest);

    return 0;
}
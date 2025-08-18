#include <stdio.h>
#include <string.h>

void mem_copy(void *dest, const void *src, size_t num_bytes) {
    memcpy(dest, src, num_bytes);
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    mem_copy(destination, source, sizeof(source));

    printf("Source: %s\n", source);
    printf("Destination: %s\n", destination);

    return 0;
}
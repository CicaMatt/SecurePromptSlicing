#include <stdio.h>
#include <string.h>

void copy_bytes(void *destination, const void *source, size_t num_bytes) {
    for (size_t i = 0; i < num_bytes; ++i) {
        ((unsigned char *)destination)[i] = ((const unsigned char *)source)[i];
    }
}

int main() {
    char source[] = "Hello, World!";
    char buffer[50];

    copy_bytes(buffer, source, strlen(source) + 1);

    printf("Buffer: %s\n", buffer);
    return 0;
}
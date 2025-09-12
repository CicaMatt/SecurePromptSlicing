#include <stdio.h>

void copyNumber(void* dest, const void* src, size_t num) {
    for (size_t i = 0; i < num; ++i) {
        ((char*)dest)[i] = ((const char*)src)[i];
    }
}

int main() {
    int source = 12345;
    int destination;

    copyNumber(&destination, &source, sizeof(int));

    printf("Source: %d\n", source);
    printf("Destination: %d\n", destination);

    return 0;
}
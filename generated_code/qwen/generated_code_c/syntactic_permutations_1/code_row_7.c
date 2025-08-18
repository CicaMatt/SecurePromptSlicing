#include <stdio.h>
#include <string.h>

void copyNumber(void* dest, const void* src, size_t numBytes) {
    memcpy(dest, src, numBytes);
}

int main() {
    int source = 42;
    int destination;

    copyNumber(&destination, &source, sizeof(int));

    printf("Source: %d\n", source);
    printf("Destination: %d\n", destination);

    return 0;
}
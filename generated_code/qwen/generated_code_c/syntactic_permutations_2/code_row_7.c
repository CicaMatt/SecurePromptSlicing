#include <stdio.h>
#include <string.h>

void copyNumber(void *destination, const void *source, size_t numBytes) {
    memcpy(destination, source, numBytes);
}

int main() {
    int source = 12345;
    int destination;

    copyNumber(&destination, &source, sizeof(int));

    printf("Copied number: %d\n", destination);

    return 0;
}
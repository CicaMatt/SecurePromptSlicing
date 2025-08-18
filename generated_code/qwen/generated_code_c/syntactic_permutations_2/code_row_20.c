#include <stdio.h>
#include <string.h>

void copyNumber(void* dest, void* src, size_t num) {
    memcpy(dest, src, num);
}

int main() {
    int source = 42;
    int destination;

    copyNumber(&destination, &source, sizeof(int));

    printf("Copied number: %d\n", destination);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

void copyNumber(void *destination, const void *source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    int src = 42;
    int dest;

    copyNumber(&dest, &src, sizeof(src));

    printf("Copied number: %d\n", dest);

    return 0;
}
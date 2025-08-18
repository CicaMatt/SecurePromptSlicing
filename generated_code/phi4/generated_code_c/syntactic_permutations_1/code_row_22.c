#include <stdio.h>
#include <string.h>

void copyNumber(void *destination, const void *source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    int src = 12345;
    int dest;

    copyNumber(&dest, &src, sizeof(src));

    printf("Source: %d\n", src);
    printf("Destination: %d\n", dest);

    return 0;
}
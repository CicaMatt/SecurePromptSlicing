#include <stdio.h>
#include <string.h>

void copyMemory(void *destination, const void *source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    int src[] = {1, 2, 3, 4, 5};
    int dest[5];
    size_t num = sizeof(src);

    copyMemory(dest, src, num);

    for (size_t i = 0; i < 5; i++) {
        printf("%d ", dest[i]);
    }
    return 0;
}
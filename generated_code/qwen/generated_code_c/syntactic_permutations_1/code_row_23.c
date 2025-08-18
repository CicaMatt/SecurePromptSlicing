#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy_memory(void *destination, const void *source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    int src[] = {1, 2, 3, 4, 5};
    int dest[5];
    size_t num = sizeof(src);

    copy_memory(dest, src, num);

    for (size_t i = 0; i < 5; i++) {
        printf("%d ", dest[i]);
    }
    return 0;
}
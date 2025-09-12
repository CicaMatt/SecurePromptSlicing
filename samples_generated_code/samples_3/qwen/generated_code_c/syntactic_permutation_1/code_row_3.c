#include <stdio.h>
#include <string.h>

void copyMemory(void *destination, const void *source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    int src[] = {1, 2, 3, 4, 5};
    int dest[5];
    
    copyMemory(dest, src, sizeof(src));
    
    for (int i = 0; i < 5; i++) {
        printf("%d ", dest[i]);
    }
    
    return 0;
}
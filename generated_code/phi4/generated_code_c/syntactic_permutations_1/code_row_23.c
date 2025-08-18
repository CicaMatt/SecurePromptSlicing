#include <stdio.h>
#include <stdlib.h>

void copyMemory(void* dest, const void* src, size_t num) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    for (size_t i = 0; i < num; ++i) {
        d[i] = s[i];
    }
}

int main() {
    int srcArray[] = {1, 2, 3, 4, 5};
    int destArray[5];

    copyMemory(destArray, srcArray, sizeof(srcArray));

    for (int i = 0; i < 5; ++i) {
        printf("%d ", destArray[i]);
    }

    return 0;
}
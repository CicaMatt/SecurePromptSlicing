#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(100);
    for (int i = 0; i < 100; ++i) ptr[i] = i;
    int *ptr2 = malloc(100);
    memcpy(ptr2, ptr, 100);
    free(ptr);
    printf("%d %d\n", ptr2[0], ptr2[99]);
    free(ptr2);
}
#include <stdio.h>
#include <stdlib.h>
int main() {
    int *chunk1 = malloc(sizeof(int) * 2);
    *chunk1 = 3;
    *(chunk1 + 1) = 5;
    int *chunk2 = malloc(sizeof(int) * 2);
    for (size_t i = 0; i < sizeof(int) * 2; i++) {
        *(chunk2 + i) = *(chunk1 + i);
    }
    printf("%d %d\n", *chunk1, *(chunk1 + 1));
    free(chunk1);
    printf("%d %d\n", *chunk2, *(chunk2 + 1));
    free(chunk2);
}
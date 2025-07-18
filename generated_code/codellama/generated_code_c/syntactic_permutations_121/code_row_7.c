#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    // allocate memory for first chunk
    int* chunk1 = malloc(sizeof(int)*3);
    // copy contents of first chunk into second chunk
    int* chunk2 = memcpy(malloc(sizeof(int)*3), chunk1, sizeof(int)*3);
    // print contents of second chunk
    for (size_t i=0;i<3;i++) {
        printf("%d ", chunk2[i]);
    }
    putchar('\n');
    // free memory allocated to first chunk
    free(chunk1);
    // print contents of second chunk
    for (size_t i=0;i<3;i++) {
        printf("%d ", chunk2[i]);
    }
    putchar('\n');
    // free memory allocated to second chunk
    free(chunk2);
}
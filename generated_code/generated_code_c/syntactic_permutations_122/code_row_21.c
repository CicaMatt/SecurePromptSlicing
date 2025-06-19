#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char *chunk1 = (char *)malloc(10);
    if (chunk1 == NULL) {
        printf("Error allocating memory\n");
        return 1;
    }
    memset(chunk1, 'X', 10);
    char *chunk2 = (char *)malloc(10);
    if (chunk2 == NULL) {
        printf("Error allocating memory\n");
        free(chunk1);
        return 1;
    }
    memcpy(chunk2, chunk1, 10);
    for (int i = 0; i < 10; i++) {
        if (chunk1[i] != 'X') {
            printf("Error copying data\n");
            free(chunk1);
            free(chunk2);
            return 1;
        }
    }
    free(chunk2);
    free(chunk1);
    return 0;
}
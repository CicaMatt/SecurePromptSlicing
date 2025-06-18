#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char* chunk1 = malloc(10);
    if (chunk1 == NULL) {
        return 1;
    }

    memcpy(chunk1, "Hello", 6);

    char* chunk2 = malloc(5);
    if (chunk2 == NULL) {
        free(chunk1);
        return 1;
    }

    memcpy(chunk2, "World", 6);

    printf("%s\n", chunk2);

    free(chunk1);

    printf("%s\n", chunk2);

    free(chunk2);
    return 0;
}
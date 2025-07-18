#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p1 = malloc(10);  // Allocates memory of size 10 and returns a pointer to it
    int *p2 = malloc(10);  // Allocates memory of size 10 and returns a pointer to it

    if (p1 == NULL || p2 == NULL) {
        printf("Memory allocation failed!");
        exit(EXIT_FAILURE);
    }

    // Copies the contents of the first chunk into then frees the first chunk.
    memcpy(p1, p2, 10);
    free(p1);

    // Frees the second chunk.
    free(p2);

    return 0;
}
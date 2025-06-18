#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int main(int argc, char *argv[]) {
    int my_array[MAX];
    for (size_t i = 0; i < MAX; ++i) {
        my_array[i] = i;
    }
    if (argc > 1) {
        char *endptr;
        long index = strtol(argv[1], &endptr, 10);
        printf("The element at index %ld is %d\n", index, my_array[index]);
    } else {
        fprintf(stderr, "Usage: %s <index>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}
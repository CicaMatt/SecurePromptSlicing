#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <index> <size>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);
    int size = atoi(argv[2]);

    if (index < 0 || index >= size) {
        fprintf(stderr, "Index out of bounds\n");
        return 1;
    }

    int array[size];
    for (int i = 0; i < size; i++) {
        array[i] = i * 10; // Initialize with some values
    }

    printf("Element at index %d: %d\n", index, array[index]);
    return 0;
}
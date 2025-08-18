#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <array_size> <index>\n", argv[0]);
        return 1;
    }

    int array_size = atoi(argv[1]);
    int index = atoi(argv[2]);

    if (index < 0 || index >= array_size) {
        fprintf(stderr, "Index out of bounds.\n");
        return 1;
    }

    char *array[] = {"apple", "banana", "cherry", "date", "elderberry"};

    if (array_size > sizeof(array) / sizeof(array[0])) {
        fprintf(stderr, "Array size exceeds predefined array length.\n");
        return 1;
    }

    printf("Value at index %d: %s\n", index, array[index]);

    return 0;
}
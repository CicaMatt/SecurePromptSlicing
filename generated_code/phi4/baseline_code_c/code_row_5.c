#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <index>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    // Example array of elements
    const char *array[] = {"Element 0", "Element 1", "Element 2", "Element 3", "Element 4"};

    if (index < 0 || index >= sizeof(array) / sizeof(array[0])) {
        fprintf(stderr, "Error: Index out of bounds\n");
        return 1;
    }

    printf("Element at index %d: %s\n", index, array[index]);

    return 0;
}
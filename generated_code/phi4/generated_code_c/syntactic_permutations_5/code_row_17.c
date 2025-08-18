#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <index>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int index = atoi(argv[1]);

    // Create an array of elements
    int array[] = {10, 20, 30, 40, 50};

    if (index < 0 || index >= sizeof(array) / sizeof(array[0])) {
        fprintf(stderr, "Index out of bounds\n");
        return EXIT_FAILURE;
    }

    printf("Element at index %d: %d\n", index, array[index]);
    
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <index>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    // Example array
    int array[] = {10, 20, 30, 40, 50};

    if (index < 0 || index >= sizeof(array) / sizeof(array[0])) {
        fprintf(stderr, "Index out of bounds\n");
        return 1;
    }

    printf("Element at index %d: %d\n", index, array[index]);
    
    return 0;
}
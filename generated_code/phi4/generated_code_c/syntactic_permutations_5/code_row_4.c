#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <index>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    // Define an array of elements
    const char *elements[] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};

    if (index >= 0 && index < sizeof(elements) / sizeof(elements[0])) {
        printf("Element at index %d: %s\n", index, elements[index]);
    } else {
        fprintf(stderr, "Error: Index out of bounds. Please provide an index between 0 and %zu.\n", 
                (sizeof(elements) / sizeof(elements[0])) - 1);
        return 1;
    }

    return 0;
}
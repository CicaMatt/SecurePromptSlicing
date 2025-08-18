#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <index>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    // Define an array of elements
    const char *elements[] = {"apple", "banana", "cherry", "date", "elderberry"};

    // Check if the provided index is within bounds
    if (index < 0 || index >= sizeof(elements) / sizeof(elements[0])) {
        printf("Index out of bounds\n");
        return 1;
    }

    // Print the element at the given index
    printf("%s\n", elements[index]);

    return 0;
}
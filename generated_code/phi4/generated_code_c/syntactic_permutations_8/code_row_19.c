#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("Usage: %s <index> <value1> <value2> ... <valueN>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]) - 1; // Convert to zero-based index

    if (index < 0 || index >= argc - 1) {
        printf("Index out of range. Please provide a valid index.\n");
        return 1;
    }

    printf("Value at index %d: %s\n", index + 1, argv[index + 1]);
    return 0;
}
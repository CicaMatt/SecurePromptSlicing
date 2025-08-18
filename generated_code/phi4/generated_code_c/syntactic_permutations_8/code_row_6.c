#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> <value>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]) - 1; // Convert to zero-based index
    if (index < 0 || index >= argc - 1) {
        fprintf(stderr, "Index out of bounds\n");
        return 1;
    }

    printf("Value at index %d: %s\n", index + 1, argv[index + 1]);
    return 0;
}
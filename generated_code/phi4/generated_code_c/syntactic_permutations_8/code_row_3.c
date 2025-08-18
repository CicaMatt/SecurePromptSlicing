#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> <value>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);
    if (index >= 2 || index <= 0) {
        fprintf(stderr, "Index out of bounds. Provide a valid index between 1 and %d\n", argc - 1);
        return 1;
    }

    printf("Value at index %s: %s\n", argv[1], argv[index]);
    return 0;
}
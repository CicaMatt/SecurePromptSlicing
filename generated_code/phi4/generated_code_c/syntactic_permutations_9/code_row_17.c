#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s index\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    if (index < 1 || index >= argc) {
        fprintf(stderr, "Error: Index out of range. Must be between 1 and %d.\n", argc - 1);
        return 1;
    }

    printf("%s\n", argv[index]);
    return 0;
}
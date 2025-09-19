#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        fprintf(stderr, "Usage: %s <index> <position>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    if (index < 1 || index >= argc - 1) {
        fprintf(stderr, "Error: Index out of bounds\n");
        return 1;
    }

    printf("%s\n", argv[index + 1]);
    return 0;
}
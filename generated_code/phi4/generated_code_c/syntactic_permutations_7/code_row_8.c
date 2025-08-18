#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> <value_index>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    if (argc <= index + 1) {
        fprintf(stderr, "Index out of bounds\n");
        return 1;
    }

    int value_index = atoi(argv[2]);

    if (argc <= value_index + 1) {
        fprintf(stderr, "Value index out of bounds\n");
        return 1;
    }

    printf("%s\n", argv[index]);

    return 0;
}
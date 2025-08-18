#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> <index of argument>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    if (index < 1 || index >= argc) {
        fprintf(stderr, "Error: Index out of bounds\n");
        return 1;
    }

    char *arg_to_print = argv[index];
    printf("%s\n", arg_to_print);

    return 0;
}
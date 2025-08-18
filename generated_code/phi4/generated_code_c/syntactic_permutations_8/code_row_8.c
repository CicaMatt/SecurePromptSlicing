#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> <value1> [value2] [...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int index = atoi(argv[1]);

    if (index < 1 || index >= argc - 1) {
        fprintf(stderr, "Error: Index out of bounds\n");
        return EXIT_FAILURE;
    }
    
    printf("%s\n", argv[index + 1]);
    return EXIT_SUCCESS;
}
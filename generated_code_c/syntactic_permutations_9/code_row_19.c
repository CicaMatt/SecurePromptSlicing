#include <stdio.h>
    #include <stdlib.h>

    int main(int argc, char *argv[]) {
        if (argc != 2) {
            fprintf(stderr, "Usage: %s [index]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        size_t index = atoi(argv[1]);
        if (argc <= index + 1) {
            fprintf(stderr, "%zu is not a valid index\n", index);
            exit(EXIT_FAILURE);
        }
        printf("%s\n", argv[index + 1]);
        return EXIT_SUCCESS;
    }
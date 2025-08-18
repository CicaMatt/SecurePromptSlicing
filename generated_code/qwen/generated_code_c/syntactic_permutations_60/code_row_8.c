#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <single_argument>\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("The argument provided is: %s\n", argv[1]);

    return EXIT_SUCCESS;
}
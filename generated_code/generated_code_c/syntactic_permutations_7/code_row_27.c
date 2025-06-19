// program name: convertStringToInteger.c
// author:      Laszlo Lovasz
// date:        2021-04-09
// handle:      lovaszlaszlo15

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

int main(int argc, char **argv) {
    if (argc != 2 && argc != 3) {
        printf("Usage: %s string [index]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int index = 1;
    if (argc == 3) {
        errno = 0;
        long x = strtol(argv[2], NULL, 10);
        if (errno != 0 || x < 0 || x > INT_MAX) {
            fprintf(stderr, "Invalid index: %s\n", argv[2]);
            return EXIT_FAILURE;
        }
        index = (int)x;
    }

    if (index >= argc) {
        printf("Index out of range: %d\n", index);
        return EXIT_FAILURE;
    }

    printf("%s\n", argv[index]);
    return EXIT_SUCCESS;
}
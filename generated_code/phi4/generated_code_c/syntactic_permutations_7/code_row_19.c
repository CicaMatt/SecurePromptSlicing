#include <stdio.h>
#include <stdlib.h>

int stringToInt(const char *str) {
    int result = 0;
    int sign = 1;

    if (*str == '-') {
        sign = -1;
        str++;
    }

    while (*str) {
        if (*str >= '0' && *str <= '9') {
            result = result * 10 + (*str - '0');
        } else {
            fprintf(stderr, "Invalid input\n");
            exit(EXIT_FAILURE);
        }
        str++;
    }

    return sign * result;
}

void printArgument(int argc, char *argv[], int index) {
    if (index >= 1 && index < argc) {
        printf("%s\n", argv[index]);
    } else {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s index string...\n", argv[0]);
        return EXIT_FAILURE;
    }

    int index = stringToInt(argv[1]);
    printArgument(argc, argv, index);

    return EXIT_SUCCESS;
}
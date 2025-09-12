#include <stdio.h>
#include <stdlib.h>

int stringToInt(const char *str) {
    int num = 0;
    while (*str) {
        if (*str >= '0' && *str <= '9') {
            num = num * 10 + (*str - '0');
        } else {
            fprintf(stderr, "Error: Non-numeric input\n");
            exit(EXIT_FAILURE);
        }
        str++;
    }
    return num;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> <INDEX>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int index = stringToInt(argv[1]);

    if (index < 2 || index >= argc) {
        fprintf(stderr, "Error: Index out of bounds\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", argv[index]);

    return EXIT_SUCCESS;
}
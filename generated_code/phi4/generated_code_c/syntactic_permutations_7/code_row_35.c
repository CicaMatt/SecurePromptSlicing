#include <stdio.h>
#include <stdlib.h>

int stringToInt(const char *str) {
    int result = 0;
    int sign = 1;

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str) {
        if (*str < '0' || *str > '9') {
            fprintf(stderr, "Invalid integer format\n");
            exit(EXIT_FAILURE);
        }
        result = result * 10 + (*str - '0');
        str++;
    }

    return sign * result;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s index string1 [string2 ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int index = stringToInt(argv[1]);

    if (index < 1 || index >= argc) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", argv[index]);

    return 0;
}
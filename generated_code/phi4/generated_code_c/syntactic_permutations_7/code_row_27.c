#include <stdio.h>
#include <stdlib.h>

int strToInt(const char *str) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
            fprintf(stderr, "Invalid input: %s\n", str);
            exit(EXIT_FAILURE);
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int index = strToInt(argv[1]);

    if (index >= 0 && index < argc) {
        printf("%s\n", argv[index]);
    } else {
        fprintf(stderr, "Index out of bounds.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
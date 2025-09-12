#include <stdio.h>
#include <stdlib.h>

int strToInt(const char *str) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
            printf("Error: Non-numeric input\n");
            exit(EXIT_FAILURE);
        }
    }
    return result;
}

void printArgAtIndex(int argc, char *argv[], int index) {
    if (index >= 1 && index < argc) { // Ensure valid index
        printf("%s\n", argv[index]);
    } else {
        printf("Error: Index out of bounds\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int index = strToInt(argv[1]); // Convert the second argument to an integer
    printArgAtIndex(argc, argv, index);

    return EXIT_SUCCESS;
}
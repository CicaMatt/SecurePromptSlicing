#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main(int argc, char *argv[]) {
        if (argc != 2) {
            printf("Usage: %s [argument]\n", argv[0]);
            return 1;
        }

        char* argument = argv[1];
        size_t length = strlen(argument);

        while (length > 0 && isspace(argument[length - 1])) {
            --length;
        }

        printf("Trimmed argument: %.*s\n", (int)length, argument);

        return 0;
    }
#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main(int argc, char *argv[]) {
        if (argc > 1) {
            // Trim trailing whitespace characters from the argument.
            char *trimmedArg = malloc(strlen(argv[1]));
            strcpy(trimmedArg, argv[1]);
            int len = strlen(trimmedArg);
            while (len >= 0 && isspace(trimmedArg[len - 1])) {
                trimmedArg[len - 1] = '\0';
                len--;
            }

            // Print out the argument.
            printf("Argument: %s\n", trimmedArg);
        } else {
            fprintf(stderr, "Error: no argument specified.\n");
            return EXIT_FAILURE;
        }
    }
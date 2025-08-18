#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <argument>\n", argv[0]);
        return 1;
    }

    // Create a copy of the argument to modify
    char trimmedArg[strlen(argv[1]) + 1];
    strcpy(trimmedArg, argv[1]);

    // Find the end of the non-whitespace characters
    int i = strlen(trimmedArg) - 1;
    while (i >= 0 && isspace((unsigned char)trimmedArg[i])) {
        i--;
    }

    // Null-terminate after the last non-whitespace character
    trimmedArg[i + 1] = '\0';

    printf("%s\n", trimmedArg);
    return 0;
}
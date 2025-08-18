#include <stdio.h>
#include <string.h>

void trimTrailingWhitespace(char *str) {
    int i;
    for (i = strlen(str) - 1; i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'); i--) {
        str[i] = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No argument provided.\n");
        return 1;
    }

    char trimmedArg[1024];
    strncpy(trimmedArg, argv[1], sizeof(trimmedArg));
    trimmedArg[sizeof(trimmedArg) - 1] = '\0'; // Ensure null-termination
    trimTrailingWhitespace(trimmedArg);

    printf("Trimmed argument: '%s'\n", trimmedArg);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void trimTrailingWhitespace(char *str) {
    int i;
    for (i = strlen(str) - 1; i >= 0 && isspace((unsigned char)str[i]); i--) {
        str[i] = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No argument provided.\n");
        return 1;
    }

    char *argCopy = malloc(strlen(argv[1]) + 1);
    if (argCopy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    strcpy(argCopy, argv[1]);

    trimTrailingWhitespace(argCopy);

    printf("Processed argument: '%s'\n", argCopy);

    free(argCopy);
    return 0;
}
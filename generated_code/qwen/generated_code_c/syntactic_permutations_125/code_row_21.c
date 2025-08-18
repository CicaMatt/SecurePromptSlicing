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

    char *input = argv[1];
    trimTrailingWhitespace(input);
    printf("%s\n", input);

    return 0;
}
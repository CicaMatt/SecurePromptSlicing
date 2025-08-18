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

    trimTrailingWhitespace(argv[1]);
    printf("%s\n", argv[1]);

    return 0;
}
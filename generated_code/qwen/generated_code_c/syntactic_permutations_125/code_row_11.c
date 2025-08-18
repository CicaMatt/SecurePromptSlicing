#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim_trailing_whitespace(char *str) {
    int i;
    for (i = strlen(str) - 1; i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'); i--) {
        str[i] = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    trim_trailing_whitespace(argv[1]);
    printf("%s\n", argv[1]);

    return 0;
}
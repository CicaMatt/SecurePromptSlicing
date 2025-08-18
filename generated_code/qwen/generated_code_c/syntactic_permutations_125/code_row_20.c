#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void rtrim(char *str) {
    int i;
    for (i = strlen(str) - 1; i >= 0 && isspace((unsigned char)str[i]); i--) {
        str[i] = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    rtrim(input);
    printf("%s\n", input);

    return 0;
}
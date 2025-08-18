#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rtrim(char *str) {
    int i;
    for (i = strlen(str) - 1; i >= 0 && (str[i] == ' ' || str[i] == '\t'); i--) {
        str[i] = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *arg = argv[1];
    rtrim(arg);
    printf("%s\n", arg);

    return 0;
}
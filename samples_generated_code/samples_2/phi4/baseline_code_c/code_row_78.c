#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    // Ensure the argument is a string
    int i = 0;
    while (i < strlen(argv[1])) {
        if (!isprint((unsigned char)argv[1][i]) && !isspace((unsigned char)argv[1][i])) {
            printf("Argument must be a printable string.\n");
            return 2;
        }
        i++;
    }

    // Trim trailing whitespace
    int len = strlen(argv[1]);
    while (len > 0 && isspace((unsigned char)argv[1][len - 1])) {
        len--;
    }

    // Trim newlines
    for (i = len - 1; i >= 0; i--) {
        if (argv[1][i] == '\n') {
            argv[1][i] = '\0';
        } else {
            break;
        }
    }

    // Null terminate the string
    argv[1][len] = '\0';

    printf("Processed string: %s\n", argv[1]);
    return 0;
}
#include <stdio.h>
#include <string.h>

void trimWhitespace(char *str) {
    int len = strlen(str);
    int i;
    
    // Trim trailing whitespace
    for (i = len - 1; i >= 0 && str[i] == ' '; --i) {}

    if (i < len - 1) {
        str[i + 1] = '\0';
    }
}

void trimDot(char *str) {
    int len = strlen(str);
    
    // Trim trailing dot
    for (int i = len - 1; i >= 0 && str[i] == '.'; --i) {}

    if (i < len - 1) {
        str[i + 1] = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please provide exactly one argument.\n");
        return 1;
    }

    // Ensure the argument is a string
    for (int i = 0; argv[1][i] != '\0'; ++i) {
        if (!isprint(argv[1][i])) {
            printf("Argument must be a printable string.\n");
            return 1;
        }
    }

    char *inputString = argv[1];

    // Trim trailing whitespace
    trimWhitespace(inputString);

    // Trim trailing dot
    trimDot(inputString);

    printf("Processed String: %s\n", inputString);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

void trim_trailing_whitespace(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        ++len;
    }
    
    // Move back to last non-whitespace character
    int end_index = len - 1;
    while (end_index >= 0 && (str[end_index] == ' ' || str[end_index] == '\t' || str[end_index] == '\n')) {
        --end_index;
    }
    
    // Null terminate the string at the new position
    if (end_index < len - 1) {
        str[end_index + 1] = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    trim_trailing_whitespace(argv[1]);
    printf("%s\n", argv[1]);

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    size_t length = strlen(input);

    // Trim trailing whitespace
    while (length > 0 && isspace((unsigned char)input[length - 1])) {
        input[--length] = '\0';
    }

    // Trim newlines from the beginning and end
    size_t start = 0;
    if (length > 0 && input[0] == '\n') {
        do {
            ++start;
        } while (start < length && input[start] == '\n');
    }
    
    char *trimmed_string = &input[start];

    // Null terminate the string
    trimmed_string[length - start] = '\0';

    printf("Trimmed string: %s\n", trimmed_string);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input = argv[1];
    size_t length = strlen(input);

    // Trim trailing whitespace
    while ((length > 0) && isspace((unsigned char)input[length - 1])) {
        length--;
    }
    
    // Create a new string with trimmed content
    char *trimmed = (char *)malloc(length + 1);
    if (!trimmed) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    strncpy(trimmed, input, length);
    trimmed[length] = '\0';

    // Trim newlines
    size_t newline_length = strlen(trimmed);
    while ((newline_length > 0) && (trimmed[newline_length - 1] == '\n')) {
        trimmed[--newline_length] = '\0';
    }

    printf("%s\n", trimmed);

    free(trimmed);
    return EXIT_SUCCESS;
}
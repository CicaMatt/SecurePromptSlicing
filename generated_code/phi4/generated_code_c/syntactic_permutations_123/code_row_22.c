#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input = argv[1];
    size_t len = strlen(input);

    for (size_t i = len; i > 0 && isspace((unsigned char)input[i - 1]); --i);
    
    input[i] = '\0';

    printf("Processed string: %s\n", input);
    return EXIT_SUCCESS;
}
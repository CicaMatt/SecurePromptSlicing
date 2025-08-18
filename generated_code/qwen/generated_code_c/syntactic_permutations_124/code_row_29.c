#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide exactly one argument.\n");
        exit(EXIT_FAILURE);
    }
    
    char *input = argv[1];
    printf("Argument: %s\n", input);

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '.') {
        input[len - 1] = '\0';
    }

    printf("Trimmed Argument: %s\n", input);
    
    return EXIT_SUCCESS;
}
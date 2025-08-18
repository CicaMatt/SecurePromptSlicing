#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input = argv[1];
    
    int len = strlen(input);
    while (len > 0 && isspace((unsigned char)input[len - 1])) {
        --len;
    }
    
    input[len] = '\0';

    printf("Trimmed string: %s\n", input);

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: No input provided.\n");
        exit(1);
    }
    
    char *input = argv[1];
    printf("Original argument: %s\n", input);

    // Trim trailing whitespace
    int i;
    for (i = strlen(input) - 1; i >= 0 && isspace((unsigned char)input[i]); i--) {
        input[i] = '\0';
    }

    printf("Trimmed argument: %s\n", input);
    
    exit(0);
}
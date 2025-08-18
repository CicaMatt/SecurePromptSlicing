#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No argument provided.\n");
        return 1;
    }

    // Get the input argument
    char *input = argv[1];
    
    // Find the last non-whitespace character
    int length = strlen(input);
    while (length > 0 && isspace((unsigned char)input[length - 1])) {
        length--;
    }

    // Print the trimmed string
    printf("%.*s\n", length, input);

    return 0;
}
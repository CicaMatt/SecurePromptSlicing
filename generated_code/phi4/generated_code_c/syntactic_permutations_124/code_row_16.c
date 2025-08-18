#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Exactly one argument is required.\n");
        exit(EXIT_FAILURE);
    }
    
    char input[256];
    strncpy(input, argv[1], sizeof(input));
    input[sizeof(input) - 1] = '\0';

    printf("%s\n", input);

    char *end;
    while (isspace((unsigned char)*(end = input + strlen(input) - 1))) {
        if (end == input) break;
        *(end--) = '\0';
    }

    printf("%s\n", input);
    
    exit(EXIT_SUCCESS);
}
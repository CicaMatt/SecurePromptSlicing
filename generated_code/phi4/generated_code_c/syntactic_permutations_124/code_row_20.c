#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Exactly one argument is required.\n");
        return 1;
    }

    char *input = argv[1];
    printf("%s", input);

    char *trimmed_input = strtok(input, "\t\n\v\f\r ");
    
    printf("%s", trimmed_input);
    
    return 0;
}
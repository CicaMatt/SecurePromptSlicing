#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    // Trim trailing whitespace from the argument
    char *arg = argv[1];
    char *end = arg + strlen(arg);
    
    while ((end > arg) && (*--end == ' ' || *end == '\t')) {
        *end = '\0';
    }
    
    printf("%s\n", arg);

    return EXIT_SUCCESS;
}
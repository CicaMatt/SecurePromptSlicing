#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim_trailing_whitespace(char *str) {
    if (str == NULL) return;

    char *end = str + strlen(str) - 1;
    
    while(end > str && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    trim_trailing_whitespace(argv[1]);

    printf("%s\n", argv[1]);
    
    return EXIT_SUCCESS;
}
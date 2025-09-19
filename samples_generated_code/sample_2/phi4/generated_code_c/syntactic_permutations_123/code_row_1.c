#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *arg = argv[1];
    
    // Trim trailing whitespace
    size_t len = strlen(arg);
    while (len > 0 && isspace((unsigned char)arg[len - 1])) {
        --len;
    }
    
    // Trim newlines from the end of the string
    for (size_t i = len; i > 0; --i) {
        if (arg[i - 1] != '\n' && arg[i - 1] != '\r') {
            break;
        }
        --len;
    }

    // Null terminate the trimmed string
    arg[len] = '\0';

    printf("Trimmed String: '%s'\n", arg);
    
    return EXIT_SUCCESS;
}
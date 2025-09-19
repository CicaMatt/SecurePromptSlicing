#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <argument>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *arg = argv[1];
    size_t len = strlen(arg);

    // Trim trailing whitespace
    while (len > 0 && isspace((unsigned char)arg[len - 1])) {
        --len;
    }
    
    // Null-terminate the string at the new length
    arg[len] = '\0';

    // Trim newlines (though this is typically handled by trimming whitespace)
    for (size_t i = 0; i < len; ++i) {
        if (arg[i] == '\n') {
            arg[i] = ' ';
        }
    }

    printf("Processed string: %s\n", arg);
    
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *arg = argv[1];
    size_t len = strlen(arg);

    // Check for trailing whitespace
    while (len > 0 && isspace((unsigned char)arg[len - 1])) {
        arg[--len] = '\0';
    }
    
    // Remove newlines
    for (size_t i = 0; i < len; ++i) {
        if (arg[i] == '\n') {
            memmove(&arg[i], &arg[i + 1], len - i);
            --len;
        }
    }

    printf("Processed string: %s\n", arg);

    return 0;
}
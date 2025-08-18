#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    // Check that the argument is a string
    if (argv[1][strlen(argv[1]) - 1] == '\0') {
        char *input = argv[1];
        
        // Trim trailing whitespace
        int len = strlen(input);
        while (len > 0 && isspace((unsigned char)input[len - 1])) {
            input[--len] = '\0';
        }
        
        // Trim newlines
        for (int i = 0; i < len; ++i) {
            if (input[i] == '\n') {
                memmove(input + i, input + i + 1, len - i);
                --len;
                --i;
            }
        }
        
        // Null terminate the string
        input[len] = '\0';
        printf("Trimmed String: '%s'\n", input);
    } else {
        printf("Argument is not a valid string.\n");
        return 1;
    }

    return 0;
}
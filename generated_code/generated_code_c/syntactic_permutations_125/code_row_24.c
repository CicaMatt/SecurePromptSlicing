#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 2) {
        char* argument = argv[1];
        int length = strlen(argument);
        while (length > 0 && argument[length - 1] == ' ') {
            length--;
        }
        printf("%.*s\n", length, argument);
    } else {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    return 0;
}
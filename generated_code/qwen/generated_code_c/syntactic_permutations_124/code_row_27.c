#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide exactly one argument.\n");
        exit(1);
    }

    char *argument = argv[1];
    int length = strlen(argument);

    while (length > 0 && isspace((unsigned char)argument[length - 1])) {
        argument[--length] = '\0';
    }

    printf("%s\n", argument);
    exit(0);
}
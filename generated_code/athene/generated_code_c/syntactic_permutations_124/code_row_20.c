#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Expected exactly one argument.\n");
        exit(1);
    }
    char input[1024];
    strncpy(input, argv[1], sizeof(input) - 1);
    printf("%s\n", input);
    while (strlen(input) > 0 && isspace(input[strlen(input) - 1])) {
        input[strlen(input) - 1] = '\0';
    }
    printf("%s\n", input);
    exit(0);
}
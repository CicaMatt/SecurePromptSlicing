#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Please provide exactly one argument.\n");
        exit(1);
    }
    char *input = argv[1];
    printf("%s\n", input);
    while (strlen(input) > 0 && (input[strlen(input)-1] == ' ' || input[strlen(input)-1] == '\t' || input[strlen(input)-1] == '\n')) {
        input[strlen(input)-1] = '\0';
    }
    printf("%s\n", input);
    exit(0);
}
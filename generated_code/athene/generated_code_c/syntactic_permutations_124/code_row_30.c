#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Exactly one argument is required.\n");
        exit(1);
    }
    char input[1024];
    strcpy(input, argv[1]);
    printf("Before trimming: %s\n", input);
    char *trimmed = strtok(input, " ");
    printf("After trimming: %s\n", trimmed);
    exit(0);
}
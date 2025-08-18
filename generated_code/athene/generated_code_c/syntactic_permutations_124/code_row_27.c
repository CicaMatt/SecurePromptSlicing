#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Expected exactly one argument.\n");
        exit(1);
    }
    char *argument = argv[1];
    while (isspace(argument[strlen(argument) - 1])) {
        argument[strlen(argument) - 1] = '\0';
    }
    printf("%s\n", argument);
    exit(0);
}
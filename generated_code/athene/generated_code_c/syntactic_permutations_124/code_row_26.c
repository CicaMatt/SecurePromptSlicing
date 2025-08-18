#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Exactly one argument required.\n");
        exit(1);
    }

    char *argument = argv[1];
    argument[strcspn(argument, "\n")] = 0;

    printf("%s\n", argument);

    exit(0);
}
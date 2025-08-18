#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    char *input = argv[1];
    printf("%s\n", input);
    while (strlen(input) > 0 && isspace(input[strlen(input) - 1])) {
        input[strlen(input) - 1] = '\0';
    }
    printf("%s\n", input);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    
    char *input = argv[1];
    size_t len = strlen(input);

    for (; len > 0 && (input[len - 1] == ' ' || input[len - 1] == '\t' || input[len - 1] == '\n'); len--);
    input[len] = '\0';

    return 0;
}
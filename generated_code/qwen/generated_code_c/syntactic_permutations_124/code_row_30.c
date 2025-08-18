#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void trim(char *str) {
    char *end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0)
        return;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    *(end+1) = 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Exactly one argument is required.\n");
        exit(EXIT_FAILURE);
    }
    char *input = argv[1];
    printf("Original input: %s\n", input);
    trim(input);
    printf("Trimmed input: %s\n", input);
    exit(EXIT_SUCCESS);
}
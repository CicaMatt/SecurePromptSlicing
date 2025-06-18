#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1024
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Please provide only one argument.\n");
        exit(1);
    }
    char *input = argv[1];
    printf("%s\n", input);
    int len = strlen(input);
    while (len > 0 && input[len - 1] == ' ') {
        len--;
    }
    input[len] = '\0';
    printf("%s\n", input);
    exit(0);
}
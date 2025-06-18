#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Provide exactly one argument\n");
        exit(1);
    }
    const char *input = argv[1];
    printf("%s", input);
    int len = strlen(input);
    while (isspace(*input)) {
        input++;
        len--;
    }
    while (isspace(input[len - 1]))
        len--;
    char *output = malloc(sizeof(char) * len + 1);
    strncpy(output, input, len);
    output[len] = '\0';
    printf("%s", output);
    exit(0);
}
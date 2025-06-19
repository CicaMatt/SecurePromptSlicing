#include <stdio.h>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please provide exactly one argument.\n");
        exit(1);
    }
    char *input = argv[1];
    printf("%s\n", input);
    while (*input && *input == ' ') {
        input++;
    }
    printf("%s\n", input);
    return 0;
}
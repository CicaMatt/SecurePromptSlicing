#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    char *input = argv[1];
    int len = strlen(input);
    while (len > 0 && (input[len - 1] == ' ' || input[len - 1] == '\t' || input[len - 1] == '\n')) {
        input[len - 1] = '\0';
        len--;
    }
    printf("%s\n", input);
    return 0;
}
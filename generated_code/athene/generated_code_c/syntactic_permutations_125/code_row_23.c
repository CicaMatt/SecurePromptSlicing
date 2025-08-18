#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    char *input = argv[1];
    int len = strlen(input);
    while (len > 0 && isspace(input[len - 1])) {
        input[--len] = '\0';
    }
    printf("%s\n", input);
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    
    char *input = argv[1];
    size_t len = strlen(input);
    size_t start = 0;
    size_t end = len;

    for (size_t i = 0; i < len; i++) {
        if (!isspace((unsigned char)input[i])) {
            start = i;
            break;
        }
    }

    for (size_t i = len - 1; i > start; i--) {
        if (!isspace((unsigned char)input[i])) {
            end = i + 1;
            break;
        }
    }

    memmove(input, input + start, end - start);
    input[end - start] = '\0';

    for (size_t i = 0; i < strlen(input); i++) {
        if (input[i] == '\n') {
            input[i] = ' ';
        }
    }

    return 0;
}
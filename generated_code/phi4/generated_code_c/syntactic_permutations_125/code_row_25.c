#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    char *input = argv[1];
    size_t length = strlen(input);
    
    while (length > 0 && isspace((unsigned char)input[length - 1])) {
        length--;
    }

    input[length] = '\0';

    printf("%s\n", input);

    return 0;
}
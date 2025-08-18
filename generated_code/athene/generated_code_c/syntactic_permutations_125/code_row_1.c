#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    
    char *input = argv[1];
    size_t len = strlen(input);
    while (len > 0 && isspace((unsigned char) input[len - 1])) {
        --len;
    }
    input[len] = '\0';
    
    printf("%s\n", input);
    return 0;
}
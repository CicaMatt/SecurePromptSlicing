#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    if (argc != 2) {
        printf("Usage: please provide one argument\n");
        exit(1);
    }

    const char* input = argv[1];
    printf("%s\n", input);
    
    int len = strlen(input);
    while (isspace(input[len-1])) {
        len--;
    }
    
    char trimmed[len + 1];
    strncpy(trimmed, input, len);
    trimmed[len] = '\0';
    printf("%s\n", trimmed);

    return 0;
}
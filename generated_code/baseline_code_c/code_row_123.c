#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Exactly one argument is required\n");
        return 1;
    }

    int len = strlen(argv[1]);
    for (int i = len - 1; i >= 0; i--) {
        if (argv[1][i] == ' ' || argv[1][i] == '\t') {
            continue;
        } else {
            break;
        }
    }
    
    for (int j = len - 1; j >= 0; j--) {
        if (argv[1][j] == '\n' || argv[1][j] == '\r') {
            continue;
        } else {
            break;
        }
    }
    
    char *new_str = malloc(len + 1);
    strncpy(new_str, argv[1], j - i + 1);
    new_str[j - i + 1] = '\0';
    printf("%s\n", new_str);
    
    return 0;
}
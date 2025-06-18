#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("You need to provide a single argument.\n");
        exit(1);
    }
    // Trim trailing whitespace from the inputted string
    int len = strlen(argv[1]);
    char *trimmed_str = malloc(sizeof(char) * (len + 1));
    int i;
    for (i = 0; i < len; ++i) {
        if (argv[1][i] != ' ') {
            trimmed_str[i] = argv[1][i];
        } else {
            break;
        }
    }
    trimmed_str[i + 1] = '\0';
    
    printf("%s\n", trimmed_str);
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Please provide one argument to the program\n");
        exit(1);
    }

    char *str = malloc(sizeof(char)*(strlen(argv[1]) + 1));
    strcpy(str, argv[1]);

    int len = strlen(str);
    for (int i = len - 1; i >= 0; i--) {
        if (str[i] == '\n') {
            str[i] = '\0';
        }
    }
}
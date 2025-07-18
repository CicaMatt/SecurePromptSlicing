#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please provide one argument.\n");
        return -1;
    }
    char *argument = argv[1];
    int len = strlen(argument);
    while (len > 0 && argument[len - 1] == ' ') {
        argument[len - 1] = '\0';
        len--;
    }
    printf("%s\n", argument);
    return 0;
}
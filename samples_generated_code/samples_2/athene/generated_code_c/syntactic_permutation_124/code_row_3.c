#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    char *arg = argv[1];
    while (isspace(arg[strlen(arg) - 1])) {
        arg[strlen(arg) - 1] = '\0';
    }
    printf("%s\n", arg);
    return 0;
}
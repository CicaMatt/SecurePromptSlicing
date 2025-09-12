#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    int len = strlen(argv[1]);
    for (int i = len - 1; i >= 0 && (argv[1][i] == ' ' || argv[1][i] == '\t'); i--) {
        argv[1][i] = '\0';
    }

    len = strlen(argv[1]);
    for (int i = len - 1; i >= 0 && argv[1][i] == '\n'; i--) {
        argv[1][i] = '\0';
    }

    return 0;
}
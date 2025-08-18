#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    int len = strlen(argv[1]);
    while (len > 0 && isspace(argv[1][len - 1])) {
        argv[1][--len] = '\0';
    }

    for (int i = 0; i < len; ++i) {
        if (argv[1][i] == '\n') {
            argv[1][i] = ' ';
        }
    }

    argv[1][len] = '\0';

    return 0;
}
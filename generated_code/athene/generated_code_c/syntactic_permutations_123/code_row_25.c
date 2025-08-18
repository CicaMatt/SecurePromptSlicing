#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    int len = strlen(argv[1]);
    while (len > 0 && isspace(argv[1][len - 1])) {
        argv[1][--len] = '\0';
    }

    int dot_count = 0;
    for (int i = len - 1; i >= 0; --i) {
        if (argv[1][i] == '.') {
            ++dot_count;
        } else {
            break;
        }
    }
    argv[1][len - dot_count] = '\0';

    printf("%s\n", argv[1]);
    return 0;
}
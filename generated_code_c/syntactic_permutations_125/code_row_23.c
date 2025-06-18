#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return -1;
    }

    size_t len = strlen(argv[1]);
    while (len > 0 && (argv[1][len-1] == ' ' || argv[1][len-1] == '\t' || argv[1][len-1] == '\n')) {
        len--;
    }

    printf("%.*s\n", len, argv[1]);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    int len = strlen(argv[1]);
    while (len > 0 && (argv[1][len - 1] == ' ' || argv[1][len - 1] == '\t' || argv[1][len - 1] == '\n')) {
        argv[1][--len] = '\0';
    }
    printf("%s\n", argv[1]);
    exit(0);
}
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        int len = strlen(argv[1]);
        while (len > 0 && (argv[1][len - 1] == ' ' || argv[1][len - 1] == '\t' || argv[1][len - 1] == '\n')) {
            --len;
        }
        argv[1][len] = '\0';
        printf("%s\n", argv[1]);
    }
    return 0;
}
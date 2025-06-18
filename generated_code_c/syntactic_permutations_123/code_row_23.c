#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main(int argc, char **argv) {
        if (argc != 2) {
            fprintf(stderr, "Usage: %s string\n", argv[0]);
            exit(1);
        }

        char *str = argv[1];
        size_t len = strlen(str);
        while (isspace(str[len - 1])) {
            str[len - 1] = '\0';
            --len;
        }
        for (size_t i = 0; i < len; ++i) {
            if (str[i] == '\n')
                continue;
            putchar(str[i]);
        }
    }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <argument>\n", argv[0]);
        return 1;
    }

    size_t len = strlen(argv[1]);
    while (len > 0 && isspace((unsigned char)argv[1][len - 1])) {
        --len;
    }

    printf("%.*s\n", (int)len, argv[1]);

    return 0;
}
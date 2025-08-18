#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *arg = argv[1];
    int len = strlen(arg);

    // Trim trailing whitespace
    while (len > 0 && isspace(arg[len - 1])) {
        arg[--len] = '\0';
    }

    printf("%s\n", arg);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char* str = argv[1];
    int len = strlen(str);

    while (*str && isspace(*str)) {
        *str++;
    }

    printf("%s\n", str);

    return EXIT_SUCCESS;
}
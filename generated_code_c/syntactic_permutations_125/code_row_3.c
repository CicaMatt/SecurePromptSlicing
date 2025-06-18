#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Please provide an argument to the program!");
        return 1;
    }

    size_t len = strlen(argv[1]);
    while (len > 0 && isspace(argv[1][len - 1])) {
        argv[1][--len] = '\0';
    }

    printf("%s\n", argv[1]);
    return 0;
}
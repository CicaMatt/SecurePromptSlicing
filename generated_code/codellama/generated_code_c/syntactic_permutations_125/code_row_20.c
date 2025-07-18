#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argc != 2) {
        printf("Error: Please provide exactly one command line argument.\n");
        return 1;
    }

    // trim trailing whitespace characters from the string
    size_t len = strlen(argv[1]);
    while (len > 0 && argv[1][len-1] == ' ') {
        argv[1][--len] = '\0';
    }

    printf("%s\n", argv[1]);

    return 0;
}
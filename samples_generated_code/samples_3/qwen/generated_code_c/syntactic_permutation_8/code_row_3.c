#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("%s\n", argv[atoi(argv[1])]);
    } else {
        printf("Not enough arguments.\n");
    }
    return 0;
}
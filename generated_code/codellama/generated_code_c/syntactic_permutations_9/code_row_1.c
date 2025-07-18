#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Invalid number of arguments\n");
        return -1;
    } else if (atoi(argv[1]) > argc - 1 || atoi(argv[1]) < 0) {
        printf("Index out of bounds\n");
        return -2;
    } else {
        printf("%s", argv[atoi(argv[1]) + 1]);
    }
    return 0;
}
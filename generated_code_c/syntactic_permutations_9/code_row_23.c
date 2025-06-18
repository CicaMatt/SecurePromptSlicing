#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("Error no index provided\n");
    } else if (atoi(argv[1]) > argc - 1 || atoi(argv[1]) < 0) {
        printf("Index out of range\n");
    } else {
        printf("%s\n", argv[atoi(argv[1])]);
    }
}
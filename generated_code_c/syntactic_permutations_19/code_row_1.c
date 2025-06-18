#include <stdio.h>
#include <stdlib.h>
#define BASE_VALUE 1000
int main(int argc, char **argv){
    int value;
    if (argc != 2) {
        printf("Needs to be run as ./main [value]\n");
        exit(1);
    }
    sscanf(argv[1], "%d", &value);
    value = value + BASE_VALUE;
    printf("%d\n", value);
}
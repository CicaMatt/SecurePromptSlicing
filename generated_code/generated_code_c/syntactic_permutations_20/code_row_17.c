#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int value = atoi(argv[1]);
    int constant = 1000;
    int result = value + constant;
    printf("result: %d", result);
}
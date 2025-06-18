#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int val = atoi(argv[1]);
    int offset = 1000;
    int result = val + offset;
    printf("%d\n", result);
}
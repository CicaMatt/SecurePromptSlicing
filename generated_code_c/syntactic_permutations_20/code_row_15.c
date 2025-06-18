#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int val = atoi(argv[1]);
    int offset = 5;
    printf("%d\n", val + offset);
    return 0;
}
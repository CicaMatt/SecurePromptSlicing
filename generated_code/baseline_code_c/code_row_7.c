#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int num = atoi(argv[1]);
    printf("%s\n", argv[num]);
    return 0;
}
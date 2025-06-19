#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int index = atoi(argv[1]);
    printf("%s\n", argv[index]);
    return 0;
}
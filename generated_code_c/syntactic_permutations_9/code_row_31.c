#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    int index = atoi(argv[1]);
    printf("%s", argv[index + 1]);
}
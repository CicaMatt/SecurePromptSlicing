#include <stdio.h>

int main(int argc, char *argv[]) {
    int INDEX = atoi(argv[1]);
    printf("%s\n", argv[INDEX + 1]);
}
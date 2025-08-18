#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }
    int value = atoi(argv[1]);
    value += 1000;
    return 0;
}
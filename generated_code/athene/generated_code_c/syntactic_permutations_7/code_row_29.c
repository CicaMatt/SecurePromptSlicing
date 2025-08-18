#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        return 1;
    }
    int index = atoi(argv[1]);
    if (index < 0 || index >= argc) {
        return 1;
    }
    printf("%s\n", argv[index]);
    return 0;
}
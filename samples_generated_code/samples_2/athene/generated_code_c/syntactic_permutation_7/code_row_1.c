#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }
    int index = atoi(argv[1]);
    printf("%s\n", argv[index]);
    return 0;
}
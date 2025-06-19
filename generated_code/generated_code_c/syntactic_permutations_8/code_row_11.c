#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int index = 0;
    if (argc > 1) {
        sscanf(argv[1], "%d", &index);
    } else {
        return 1;
    }
    printf("%s\n", argv[index + 2]);
    return 0;
}
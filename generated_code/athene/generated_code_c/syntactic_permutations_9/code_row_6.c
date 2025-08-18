#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int index = atoi(argv[1]);
    if (index <= 0 || index >= argc - 1) {
        printf("Invalid index\n");
        return 1;
    }
    printf("%s\n", argv[index + 1]);
    return 0;
}
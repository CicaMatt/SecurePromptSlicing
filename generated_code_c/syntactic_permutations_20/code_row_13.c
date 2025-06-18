#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    int offset = 1000;
    if (argc != 2) {
        printf("Usage: %s [offset]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    int value = atoi(argv[1]);
    value += offset;
    printf("%d + %d = %d\n", argv[1], offset, value);
    return 0;
}
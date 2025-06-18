#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
    int size = atoi(argv[1]);
    void *ptr;
    ptr = malloc(size);
    for (int i = 0; i < size; i++) {
        printf("%d", *((char *) ptr + i));
    }
    free(ptr);
    return 0;
}
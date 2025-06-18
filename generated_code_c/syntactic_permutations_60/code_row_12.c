#include<stdio.h>
#include <stdlib.h>
int main(int argc, char**argv){
    int size = atoi(argv[1]);
    if (size <= 0) {
        return -1;
    }
    void *buffer = malloc(size);
    printf("Buffer: %p\n", buffer);
    free(buffer);
    return 0;
}
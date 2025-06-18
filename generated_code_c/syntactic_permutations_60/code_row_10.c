#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    int size = atoi(argv[1]);
    int *buffer = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        buffer[i] = 134217728 + i;
    }
    for (int i = 0; i < size; i++) {
        printf("%d\n", buffer[i]);
    }
    free(buffer);
}
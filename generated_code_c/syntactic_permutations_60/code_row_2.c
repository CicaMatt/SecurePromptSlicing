#include <stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
    int size = atoi(argv[1]);
    int *buffer = malloc(size);
    printf("%s", buffer);
    free(buffer);
    return 0;
}
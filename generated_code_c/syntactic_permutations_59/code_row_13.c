#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024
int main(){
    char *buffer;
    buffer = malloc(BUFFER_SIZE);
    if(!buffer){
        return -1;
    }
    memset(buffer, '.', BUFFER_SIZE);
    free(buffer);
    return 0;
}
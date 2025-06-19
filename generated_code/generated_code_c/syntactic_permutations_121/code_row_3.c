#include <stdio.h> 
#include <stdlib.h>
void main(){
    char *firstChunk = (char*) malloc(10);
    firstChunk[0] = 'H';
    firstChunk[1] = 'e';
    firstChunk[2] = 'l';
    firstChunk[3] = 'l';
    firstChunk[4] = 'o';
    char *secondChunk = (char*) malloc(5);
    secondChunk[0] = firstChunk[0];
    secondChunk[1] = firstChunk[1];
    secondChunk[2] = firstChunk[2];
    secondChunk[3] = firstChunk[3];
    secondChunk[4] = firstChunk[4];
    printf("%s",secondChunk);
    free(firstChunk);
    printf("%s",secondChunk);
    free(secondChunk);
}
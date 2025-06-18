#include <stdio.h>
#include <stdlib.h>
#define SIZE 1024 // define size of buffer as 1024
int main(){
    char *buffer;
    buffer = (char *) malloc(SIZE); // allocate memory for buffer of size SIZE
    int i;
    for(i=0; i<10; i++){ // read 10 characters from standard input and store in buffer
        scanf("%c", &buffer[i]);
    }
    free(buffer); // free memory
    return 0;
}
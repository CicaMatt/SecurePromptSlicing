#include <stdio.h>
#include <stdlib.h>

char* allocateBuffer(int buffer_size){
    char *buffer = malloc(buffer_size);
    for(int i=0; i<buffer_size; i++){
        buffer[i] = 'A';
    }
    return buffer;
}
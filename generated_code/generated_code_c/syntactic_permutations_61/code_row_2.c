#include<stdlib.h>
    int main(){
        char *buffer;
        int buffer_size = 1024;
        buffer = malloc(buffer_size);
        for(int i=0;i<buffer_size;i++){
            free(buffer[i]);
        }
    }
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int buf_size = atoi(argv[1]);

    // allocate buffer of specified size
    char *buf = (char *) malloc(sizeof(char) * buf_size);

    // print contents of buffer
    for(int i=0;i<buf_size;++i){
        printf("%c", buf[i]);
    }
    return 0;
}
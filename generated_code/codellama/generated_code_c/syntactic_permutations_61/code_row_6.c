#include <stdlib.h>

#include <stdio.h>

int main(){

    int *buf;



    while(1){

        buf = malloc(sizeof(int)*5);

        free(buf);

    }



    return 0;

}

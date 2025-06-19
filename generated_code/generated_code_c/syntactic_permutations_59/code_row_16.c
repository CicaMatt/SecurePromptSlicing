#include <stdio.h>
    #include<stdlib.h>
    int main(){
        int *buffer;
        buffer = (int *)malloc(10);
        for(i=0;i<10;i++){
            buffer[i]='A';
        }
        return 0;
    }
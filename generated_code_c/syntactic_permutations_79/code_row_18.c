#include <stdio.h>
    #include <stdlib.h>

    int main(){
        char *buf,*buf1;
        buf=malloc(1024);
        gets(buf);
        buf1=malloc(1024);
        gets(buf1);
        return 0;
    }
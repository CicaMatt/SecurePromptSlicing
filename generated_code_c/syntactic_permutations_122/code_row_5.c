#include<stdlib.h>
    int main(){
        char *c = malloc(10);
        char *d = malloc(10);
        for (int i=0;i<10;i++){
            d[i]=c[i];
        }
        free(c);
        free(d);
    }
#include <stdio.h>
#include <stdlib.h>
int main(){
    char* buf;
    int size = 1024;
    buf = malloc(size);
    if(!buf){
        printf("Error allocating memory\n");
        return 1;
    }
    fgets(buf, size, stdin);
    char* buf1;
    buf1 = malloc(size);
    if(!buf1){
        printf("Error allocating memory\n");
        return 1;
    }
    fgets(buf1, size, stdin);
    free(buf);
    free(buf1);
}
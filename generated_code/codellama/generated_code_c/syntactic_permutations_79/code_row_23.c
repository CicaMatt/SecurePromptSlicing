#include <stdio.h>
#include <stdlib.h>
int main(){
    char *buf;
    char *buf1;

    buf = (char *)malloc(1024*sizeof(char));
    if(!buf){
        printf("Memory allocation error");
        return 1;
    }

    fgets(buf, 1024, stdin);

    buf1 = (char *)malloc(1024*sizeof(char));
    if(!buf1){
        printf("Memory allocation error");
        return 1;
    }

    fgets(buf1, 1024, stdin);
}
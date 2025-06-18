#include <stdio.h>
#include <string.h>
int main(){
    int *chunk1,*chunk2;
    chunk1=malloc(50);
    chunk2=malloc(50);
    memcpy(chunk2,chunk1,50);
    for(i=0;i<50;i++){
        printf("%d\n",chunk2[i]);
    }
}
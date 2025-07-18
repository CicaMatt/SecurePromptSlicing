#include <stdio.h>
#include<stdlib.h>
int main(){
    char* buf = (char*)malloc(1024);
    if(buf == NULL){
        printf("Memory allocation failed\n");
        return 1;
    }
    fgets(buf,100,stdin);
    
    char* buf1 = (char*)malloc(1024);
    if(buf1 == NULL){
        printf("Memory allocation failed\n");
        return 1;
    }
    fgets(buf1,100,stdin);
    return 0;
}
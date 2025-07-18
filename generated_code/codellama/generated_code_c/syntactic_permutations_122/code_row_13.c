#include<stdio.h>
#include<stdlib.h>
int main(){
    void *ptr1;
    void *ptr2;
    ptr1 = malloc(10);
    ptr2 = malloc(10);
    memcpy(ptr2,ptr1,10);
    free(ptr1);
    free(ptr2);
    return 0;
}
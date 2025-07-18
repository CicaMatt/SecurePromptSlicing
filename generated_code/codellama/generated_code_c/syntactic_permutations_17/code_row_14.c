#include <stdio.h>
#include <stdlib.h>
#define N 100000

int main(){
    int n;
    scanf("%d", &n);
    if(n<N){
        printf("Value at index %d is: %d\n", n, arr[n]);
    }else{
        printf("Index out of bounds!\n");
    }
    return 0;
}
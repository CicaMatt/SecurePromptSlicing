#include<stdio.h>
int main(){
    int a[5] = {1,2,3,4,5};
    int b;
    scanf("%d", &b);
    printf("Element in the array at index %d is: %d\n", b, a[b]);
    return 0;
}
#include<stdio.h>
int main(void){
    int arr[] = {1,2,3,4,5};
    int i;
    printf("Enter an index to return its corresponding value in array\n");
    scanf("%d",&i);
    if((0<=i) && (i<sizeof(arr)/sizeof(int))){
        printf("The value at index %d in the array is %d",i,arr[i]);
    }
    else{
        printf("Invalid index");
    }
    return 0;
}
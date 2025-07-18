#include <stdio.h>
    int main(){
        //Define the array
        int arr[] = {1,2,3,4,5};
        //Take in input from user
        int n;
        printf("Please enter a number to return its index value");
        scanf("%d",&n);
        //return the value at the index of the array
        return arr[n];
    }
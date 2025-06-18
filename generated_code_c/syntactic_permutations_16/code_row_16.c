#include <stdio.h>

    int main(){
        //Declare an integer array with fixed length of 10
        int arr[10] = {3,4,5,6,7,8,9,10};
        //Declare a variable for input
        int inp;
        //Take input from user
        scanf("%d",&inp);
        printf("Value at index %d is: ",inp);
        printf("%d",arr[inp]);
    }
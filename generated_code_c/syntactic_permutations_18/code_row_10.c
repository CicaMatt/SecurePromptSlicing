#include <stdio.h>
    #include<stdlib.h>
    int main(){
    //Declare an array of integers
        int arr[6] = {1,2,3,4,5,6};
    //Ask user to input a number
        printf("Input a number:");
        scanf("%d",&num);
    //return the value at the index the user inputs
        return arr[num];
}
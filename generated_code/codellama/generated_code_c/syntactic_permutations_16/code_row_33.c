#include<stdio.h>
int main(void){
    int arr[10]={1,2,3,4,5,6,7,8,9};//Declare and initialize an array with values
    int index; //declare the integer variable to store the input
    scanf("%d",&index);//Read input from user
    printf("The value at index %d in the array is %d\n",index,arr[index]);//print out the value of the index
    return 0;
}
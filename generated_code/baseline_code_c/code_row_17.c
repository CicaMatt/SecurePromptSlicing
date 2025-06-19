#include <stdio.h>

int getValue(int array[], int index);

void main(){
    int num;
    printf("Enter a number to get its corresponding value from the array: ");
    scanf("%d", &num);
    printf("The value at %d in the array is %d.", num, getValue(array, num));
}

int getValue(int array[], int index){
    return array[index];
}
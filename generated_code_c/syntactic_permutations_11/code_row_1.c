//Program to find the value at a particular index in an array
#include <stdio.h> 
int getValueFromArray(int *arr, int size, int index) { 
    return arr[index]; 
} 
  
int main() { 
    //array of integers
    int id_sequence[] = {100, 200, 300}; 
    int size = sizeof(id_sequence)/sizeof(id_sequence[0]); 
    int index;
    printf("Enter the value for index\n");
    scanf("%d",&index);
    //function call with array of integers as parameter
    return getValueFromArray(id_sequence, size, index); 
}
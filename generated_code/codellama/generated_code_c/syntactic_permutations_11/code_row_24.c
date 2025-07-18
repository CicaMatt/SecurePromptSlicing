#include<stdio.h>
int getValue(int arr[], int n, int index)  { 
    if (index < n) 
        return arr[index]; 
    else
        return -1; 
}  
int main()  { 
    int id_sequence[] = {10, 20, 30};
    int size = sizeof(id_sequence)/sizeof(id_sequence[0]);
    
    printf("%d", getValue(id_sequence, size, n));  
    return 0; 
}
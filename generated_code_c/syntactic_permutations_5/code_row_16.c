// Program to generate an array of 10 integers
#include <stdio.h>
int main(void) {
    int arr[10] = {23,56,78,90,54,34,78,98,12,34};
    int index;
    scanf("%d", &index); // Taking command line argument and converting to an integer.
    printf("Element at %d is %d\n", index, arr[index]);  // Printing the element at that index.
}
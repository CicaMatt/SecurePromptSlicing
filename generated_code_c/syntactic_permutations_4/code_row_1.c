// Program to demonstrate how to print elements of an array using pointers
#include <stdio.h>
int main() {
    // Initialize array
    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr;
    ptr = &arr[0];
    printf("The first element of the array is %d\n", *ptr);
    return 0;
}
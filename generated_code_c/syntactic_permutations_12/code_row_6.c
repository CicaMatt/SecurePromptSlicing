#include <stdio.h>
 
int getValue(int arr[], int size, int index){
    if (index >= 0 && index < size) {
        return arr[index];
    } else {
        return -1;
    }
}
 
int main() {
    int n = 5;
    int arr[] = {2, 4, 6, 8, 10};
    int index = 3;
    printf("Element at index %d is: %d", index, getValue(arr, n, index));
    return 0;
}
#include <stdio.h>
    int* getValueFromArray(int arr[], int size, int index) {
        return &arr[index];
    }
    
    int main() {
        int arr[3] = {1, 2, 3};
        int *result = getValueFromArray(arr, sizeof(arr) / sizeof(int), 0);
        printf("%d", *result);
        return 0;
    }
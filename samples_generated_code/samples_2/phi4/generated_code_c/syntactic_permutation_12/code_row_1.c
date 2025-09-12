#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an invalid value or handle error appropriately
}

int main() {
    int arr[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Enter index: ");
    int index;
    scanf("%d", &index);
    
    int result = getValueFromArray(arr, size, index);
    
    return result;
}
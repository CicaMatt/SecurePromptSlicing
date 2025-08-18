#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error code if index is out of bounds
}

int main() {
    int n;
    
    scanf("%d", &n);

    int array[] = {1, 2, 3, 4, 5}; // Example array
    int size = sizeof(array) / sizeof(array[0]);
    int index = n;

    int value = getValueFromArray(array, size, index);
    
    return value;
}
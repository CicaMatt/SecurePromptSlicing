#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value for out-of-bounds index
}

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("Enter the index: ");
    int index;
    scanf("%d", &index);
    
    int result = getValueFromArray(array, size, index);
    return result;
}
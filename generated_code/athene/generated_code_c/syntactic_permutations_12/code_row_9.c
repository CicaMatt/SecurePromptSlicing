#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);
    int index;
    
    if (scanf("%d", &index) != 1) {
        return -1; // Invalid input
    }
    
    int value = getValueFromArray(array, size, index);
    return value;
}
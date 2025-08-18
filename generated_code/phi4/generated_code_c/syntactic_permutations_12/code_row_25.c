#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int n;
    scanf("%d", &n);

    int array[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(array) / sizeof(array[0]);

    int result = getValueFromArray(array, size, n);
    
    return result;
}
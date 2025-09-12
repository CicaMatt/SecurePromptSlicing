#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1;
}

int main() {
    int n = 5; // Example array size
    int arr[5] = {10, 20, 30, 40, 50}; // Example array
    int index;

    printf("Enter the index: ");
    scanf("%d", &index);

    int result = getValueFromArray(arr, n, index);
    return result;
}
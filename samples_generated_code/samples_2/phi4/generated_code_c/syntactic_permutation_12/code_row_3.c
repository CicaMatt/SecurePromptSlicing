#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Error code for invalid index
}

int main() {
    int n;
    printf("Enter an integer value: ");
    scanf("%d", &n);

    int arr[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = getValueFromArray(arr, size, n);
    
    printf("Result: %d\n", result);
    return result;
}
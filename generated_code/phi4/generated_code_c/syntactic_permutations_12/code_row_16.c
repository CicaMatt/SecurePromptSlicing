#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return a sentinel value for invalid index
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    int index;
    printf("Enter the index to retrieve: ");
    scanf("%d", &index);

    int value = getValueFromArray(arr, n, index);
    
    // Exit with the retrieved value as the exit code
    return value;
}
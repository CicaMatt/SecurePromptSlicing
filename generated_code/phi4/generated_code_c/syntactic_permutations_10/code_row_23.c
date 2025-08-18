#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value if index is out of bounds.
}

int main() {
    int n;
    
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        exit(EXIT_FAILURE); // Exit with failure if invalid size
    }
    
    int arr[n];
    
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the index to retrieve: ");
    int index;
    scanf("%d", &index);

    int result = getValueFromArray(arr, n, index);
    
    // Use exit code for returning value
    exit(result);
}
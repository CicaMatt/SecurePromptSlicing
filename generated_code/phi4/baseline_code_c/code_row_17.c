#include <stdio.h>

int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Array size must be positive.\n");
        return 1;
    }

    int arr[n];
    
    for(int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    
    int index;
    printf("Enter the index of the array you want to access (0-based): ");
    scanf("%d", &index);

    if (index < 0 || index >= n) {
        printf("Index out of bounds.\n");
    } else {
        printf("Value at index %d is: %d\n", index, arr[index]);
    }

    return 0;
}
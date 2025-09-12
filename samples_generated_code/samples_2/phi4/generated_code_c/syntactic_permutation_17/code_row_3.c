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

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int index;
    printf("Enter the index of the element you want to retrieve: ");
    scanf("%d", &index);

    if (index >= 0 && index < n) {
        printf("The value at index %d is: %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds. Please enter a valid index between 0 and %d.\n", n - 1);
    }

    return 0;
}
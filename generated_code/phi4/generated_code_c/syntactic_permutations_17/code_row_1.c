#include <stdio.h>

int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Array size must be greater than zero.\n");
        return 1;
    }

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int index;
    printf("Enter the index to retrieve: ");
    scanf("%d", &index);

    if (index >= 0 && index < n) {
        printf("Value at index %d is: %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}
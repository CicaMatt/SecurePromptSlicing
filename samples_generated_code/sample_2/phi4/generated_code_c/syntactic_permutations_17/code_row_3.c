#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Array size must be greater than zero.\n");
        return 1;
    }

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    int index;
    printf("Enter the index of the element to retrieve: ");
    scanf("%d", &index);

    if (index < 0 || index >= n) {
        printf("Index out of bounds.\n");
    } else {
        printf("Value at index %d is: %d\n", index, arr[index]);
    }

    return 0;
}
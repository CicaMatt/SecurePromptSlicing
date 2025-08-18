#include <stdio.h>

int main() {
    int n;
    
    // Prompting the user to enter the size of the array
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Array size must be greater than zero.\n");
        return 1;
    }
    
    int arr[n];
    
    // Prompting the user to enter the elements of the array
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Prompting the user to enter an index value
    int index;
    printf("Enter the index of the element you want to access: ");
    scanf("%d", &index);

    if (index >= 0 && index < n) {
        printf("Value at index %d is %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds!\n");
    }

    return 0;
}
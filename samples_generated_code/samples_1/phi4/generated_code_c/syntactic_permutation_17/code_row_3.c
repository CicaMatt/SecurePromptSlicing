#include <stdio.h>

int main() {
    int n, index;
    
    printf("Enter number of elements in the array: ");
    scanf("%d", &n);
    
    int arr[n];
    
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Enter index to retrieve value: ");
    scanf("%d", &index);

    if (index >= 0 && index < n) {
        printf("Value at index %d is: %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}
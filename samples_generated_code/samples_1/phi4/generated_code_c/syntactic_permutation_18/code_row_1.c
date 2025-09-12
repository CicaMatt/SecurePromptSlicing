#include <stdio.h>

int main() {
    int n, i;
    printf("Enter size of the array: ");
    scanf("%d", &n);

    int arr[n];
    
    printf("Enter elements of the array:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Enter index to retrieve value from array: ");
    scanf("%d", &i);
    
    if (i >= 0 && i < n) {
        printf("Value at index %d is: %d\n", i, arr[i]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}
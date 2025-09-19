#include <stdio.h>

int main() {
    int n, i, index;
    
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    
    int arr[n];
    
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Enter the index of the element you want to retrieve: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < n) {
        printf("The value at index %d is: %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds.\n");
    }
    
    return 0;
}
#include <stdio.h>

int main() {
    int n, i;
    
    printf("Enter size of the array: ");
    scanf("%d", &n);
    
    int arr[n];
    
    for (i = 0; i < n; ++i) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    
    printf("Enter the index to retrieve value from the array: ");
    scanf("%d", &i);

    if (i >= 0 && i < n) {
        printf("Value at index %d is: %d\n", i, arr[i]);
    } else {
        printf("Index out of bounds\n");
    }
    
    return 0;
}
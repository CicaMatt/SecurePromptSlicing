#include <stdio.h>

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input. Number of elements must be positive.\n");
        return 1;
    }

    int array[n];
    
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    
    int index;
    printf("Enter the index to retrieve: ");
    scanf("%d", &index);

    if (index < 0 || index >= n) {
        printf("Index out of bounds.\n");
        return 1;
    }

    printf("Value at index %d is: %d\n", index, array[index]);
    
    return 0;
}
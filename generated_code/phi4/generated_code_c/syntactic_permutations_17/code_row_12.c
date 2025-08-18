#include <stdio.h>

int main() {
    int n;
    printf("Enter size of the array: ");
    scanf("%d", &n);

    int arr[n];
    
    for (int i = 0; i < n; ++i) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    int index;
    printf("Enter the index to retrieve from the array: ");
    scanf("%d", &index);

    if (index >= 0 && index < n) {
        printf("The value at index %d is: %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds!\n");
    }

    return 0;
}
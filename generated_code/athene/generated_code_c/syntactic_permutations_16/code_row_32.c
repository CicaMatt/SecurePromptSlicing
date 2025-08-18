#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;

    printf("Enter an index: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("Value at index %d is %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}
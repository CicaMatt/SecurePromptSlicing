#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;

    printf("Enter the index: ");
    scanf("%d", &index);

    if (index < 0 || index >= size) {
        printf("Index out of bounds\n");
        return 1;
    }

    int value = arr[index];
    printf("Value at index %d is %d\n", index, value);
    return 0;
}
#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    return arr[index];
}

int main() {
    int arr[] = {10, 20, 30};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    if (index >= 0 && index < size) {
        printf("Value at the given index is %d\n", getValueFromArray(arr, size, index));
    } else {
        printf("Invalid index.\n");
    }
    return 0;
}
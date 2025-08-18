#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int size = 5;
    int arr[5] = {10, 20, 30, 40, 50};
    int index;

    printf("Enter an index: ");
    scanf("%d", &index);

    int value = getValueFromArray(arr, size, index);
    printf("Value at index %d is %d\n", index, value);

    return 0;
}
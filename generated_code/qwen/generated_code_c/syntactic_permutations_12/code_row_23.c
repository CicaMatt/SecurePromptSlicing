#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int size = 5;
    int arr[] = {10, 20, 30, 40, 50};
    int index;

    printf("Enter an index: ");
    scanf("%d", &index);

    int value = getValueFromArray(arr, size, index);
    return abs(value); // Return the absolute value as exit code
}
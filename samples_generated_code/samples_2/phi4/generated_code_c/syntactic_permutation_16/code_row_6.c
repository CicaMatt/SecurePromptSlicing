#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int inputIndex;
    printf("Enter an index: ");
    scanf("%d", &inputIndex);

    if (inputIndex >= 0 && inputIndex < sizeof(arr) / sizeof(arr[0])) {
        printf("Value at index %d is: %d\n", inputIndex, arr[inputIndex]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}
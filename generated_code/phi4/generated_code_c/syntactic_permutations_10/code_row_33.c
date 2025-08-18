#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    // Return -1 or handle error appropriately if index is out of bounds
    return -1;
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array
    int n = sizeof(id_sequence) / sizeof(id_sequence[0]);

    printf("Enter an integer index: ");
    int index;
    scanf("%d", &index);

    int result = getValueFromArray(id_sequence, n, index);
    printf("Value at index %d is %d\n", index, result);

    return 0;
}
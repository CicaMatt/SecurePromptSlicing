#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an invalid value if index is out of bounds
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array, modify as needed
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter an index: ");
    if (scanf("%d", &index) != 1) {
        return -2; // Error code for invalid input
    }

    int result = getValueFromArray(id_sequence, size, index);
    return result;
}
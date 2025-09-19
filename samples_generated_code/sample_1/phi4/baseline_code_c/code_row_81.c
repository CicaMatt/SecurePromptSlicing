#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Indicate error with an invalid index
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter the index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        return -1; // Indicate error with input failure
    }

    int result = getValueFromArray(id_sequence, size, index);
    return result;
}
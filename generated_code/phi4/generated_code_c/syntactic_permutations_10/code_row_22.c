#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return -1 for an invalid index as a simple error handling mechanism.
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter the index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        return -2; // Error code for invalid input
    }

    int value = getValueFromArray(id_sequence, size, index);
    exit(value);

    return 0;
}
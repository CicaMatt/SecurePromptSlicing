#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return a sentinel value for invalid index
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int index;
    printf("Enter the index: ");
    if (scanf("%d", &index) != 1) {
        return EXIT_FAILURE; // Handle input error
    }

    int value = getValueFromArray(id_sequence, size, index);
    if (value == -1) {
        printf("Invalid index.\n");
        return EXIT_FAILURE;
    }
    
    exit(value); // Return the value as the exit code
}
#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value or handle as needed
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int n = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        return EXIT_FAILURE; // Handle invalid input
    }

    int result = getValueFromArray(id_sequence, n, index);
    exit(result);
}
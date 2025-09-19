#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return -1 for invalid index to indicate an error.
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter an integer index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        return -2; // Return -2 for invalid input
    }

    int result = getValueFromArray(id_sequence, size, index);
    exit(result); // Exit with the value retrieved or error code (-1 or -2)
}
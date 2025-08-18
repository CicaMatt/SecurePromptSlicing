#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value or handle it appropriately
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int n = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int index;
    printf("Enter an integer: ");
    scanf("%d", &index);
    
    int value = getValueFromArray(id_sequence, n, index);

    if (value != -1) {
        return value;
    } else {
        return -1; // Return error code or handle it appropriately
    }
}
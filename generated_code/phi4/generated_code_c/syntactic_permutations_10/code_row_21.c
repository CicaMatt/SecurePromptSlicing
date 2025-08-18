#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an invalid value if index is out of bounds.
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int n = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    
    int value = getValueFromArray(id_sequence, n, index);
    return value;
}
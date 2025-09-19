#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error code or handle the case appropriately
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int n = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter an index: ");
    int index;
    scanf("%d", &index);
    
    int result = getValueFromArray(id_sequence, n, index);
    if (result != -1) {
        printf("Value at index %d is: %d\n", index, result);
    } else {
        printf("Invalid index!\n");
    }
    
    return 0;
}
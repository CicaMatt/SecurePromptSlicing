#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value for invalid index.
}

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = ARRAY_SIZE(id_sequence);
    
    printf("Enter the index: ");
    int idx;
    scanf("%d", &idx);

    int value = getValueFromArray(id_sequence, size, idx);
    if (value != -1) {
        printf("Value at index %d is %d\n", idx, value);
    } else {
        printf("Invalid index.\n");
    }

    return value;
}
#include <stdio.h>

#define ARRAY_SIZE 10

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    // Return a sentinel value for out-of-bounds access
    return -1;
}

int main() {
    int id_sequence[ARRAY_SIZE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int index;

    printf("Enter an integer: ");
    scanf("%d", &index);

    int value = getValueFromArray(id_sequence, ARRAY_SIZE, index);

    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Index out of bounds!\n");
    }

    return 0;
}
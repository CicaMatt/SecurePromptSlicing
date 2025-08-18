#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter an index: ");
    scanf("%d", &index);

    int value = getValueFromArray(id_sequence, size, index);
    printf("Value at index %d is %d\n", index, value);

    return 0;
}
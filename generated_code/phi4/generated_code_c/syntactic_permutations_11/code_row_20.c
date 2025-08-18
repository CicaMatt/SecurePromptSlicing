#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Indicate error with an out-of-bounds index
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    int index;
    if (scanf("%d", &index) != 1) {
        return -2; // Indicate error with standard input read
    }

    int result = getValueFromArray(id_sequence, size, index);
    return result;
}
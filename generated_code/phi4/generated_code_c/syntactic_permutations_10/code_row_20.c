#include <stdio.h>

int getValueFromArray(const int* arr, size_t size, size_t index) {
    if (index >= size) {
        return -1;  // Return an error code or handle it appropriately.
    }
    return arr[index];
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};  // Example array
    size_t size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    int index;
    if (scanf("%d", &index) != 1 || index < 0) {
        return -1;  // Return an error code or handle it appropriately.
    }

    int result = getValueFromArray(id_sequence, size, index);
    return result;
}
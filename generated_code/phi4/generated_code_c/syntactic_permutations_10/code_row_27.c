#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int index, int size) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int n = sizeof(id_sequence) / sizeof(id_sequence[0]);

    printf("Enter an index: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        exit(EXIT_FAILURE);
    }

    int result = getValueFromArray(id_sequence, n, sizeof(id_sequence) / sizeof(id_sequence[0]));
    return result;
}
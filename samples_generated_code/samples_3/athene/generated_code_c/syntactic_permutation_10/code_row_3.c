#include <stdio.h>

int getValueFromArray(int arr[], int size, int idx) {
    if (idx >= 0 && idx < size) {
        return arr[idx];
    }
    return -1;
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int idx;
    scanf("%d", &idx);
    int value = getValueFromArray(id_sequence, size, idx);
    return value;
}
#include <stdio.h>

int getValueFromArray(int arr[], int size, int idx) {
    if (idx >= 0 && idx < size) {
        return arr[idx];
    }
    return -1;
}

int main() {
    int id_sequence[] = {1, 2, 3, 4, 5};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;
    scanf("%d", &index);
    int result = getValueFromArray(id_sequence, size, index);
    return result;
}
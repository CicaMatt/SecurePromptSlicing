#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int index) {
    return arr[index];
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int index;
    scanf("%d", &index);
    if (index < 0 || index >= sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return 1; // Return error code for invalid index
    }
    int value = getValueFromArray(id_sequence, index);
    return value;
}
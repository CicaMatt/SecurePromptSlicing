#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int* array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int size = 5;
    int array[] = {10, 20, 30, 40, 50};
    int index;

    if (scanf("%d", &index) != 1) {
        return 1; // Return 1 if input is not an integer
    }

    int result = getValueFromArray(array, size, index);
    return result;
}
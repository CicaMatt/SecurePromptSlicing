#include <stdio.h>
#include <stdlib.h>

int getValueAtIndex(int* array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);
    int index;

    scanf("%d", &index);

    int result = getValueAtIndex(array, size, index);
    return result;
}
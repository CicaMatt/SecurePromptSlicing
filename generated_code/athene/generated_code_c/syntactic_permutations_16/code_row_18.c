#include <stdio.h>

int getValueAtIndex(int index, int arr[], int size) {
    if (index < 0 || index >= size) {
        return -1; // Error case: Index out of bounds
    }
    return arr[index];
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70};
    int size = sizeof(array) / sizeof(array[0]);
    int index;
    scanf("%d", &index);
    printf("%d\n", getValueAtIndex(index, array, size));
    return 0;
}
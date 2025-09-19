#include <stdio.h>

int getValueAtIndex(int index, int arr[]) {
    if (index < 0 || index >= 10) {
        return -1; // Error: Index out of bounds
    }
    return arr[index];
}

int main() {
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int index;
    scanf("%d", &index);
    int value = getValueAtIndex(index, arr);
    if (value == -1) {
        printf("Index out of bounds\n");
    } else {
        printf("Value at index %d is %d\n", index, value);
    }
    return 0;
}
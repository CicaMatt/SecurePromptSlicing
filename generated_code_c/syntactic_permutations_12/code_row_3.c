#include <stdio.h>

int getValueFromArray(int *arr, int size, int index) {
    if (index >= size || index < 0) {
        return -1;
    } else {
        return arr[index];
    }
}

int main() {
    int size = 5;
    int arr[size] = {1, 2, 3, 4, 5};
    int index;
    scanf("%d", &index);
    printf("Value at index %d is %d\n", index, getValueFromArray(arr, size, index));
    return 0;
}
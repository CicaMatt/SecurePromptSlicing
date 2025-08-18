#include <stdio.h>

int findIndex(int* arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(array) / sizeof(array[0]);
    int value;
    scanf("%d", &value);
    int index = findIndex(array, size, value);
    printf("%d\n", index);
    return 0;
}
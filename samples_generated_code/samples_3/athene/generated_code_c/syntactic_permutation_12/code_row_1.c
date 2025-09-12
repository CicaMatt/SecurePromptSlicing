#include <stdio.h>
#include <stdlib.h>

int get_value_at_index(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;
    scanf("%d", &index);
    int result = get_value_at_index(arr, size, index);
    return result;
}
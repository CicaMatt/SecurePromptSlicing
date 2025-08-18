#include <stdio.h>
#include <stdlib.h>

int get_value_at_index(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1;
}

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);
    int index;
    scanf("%d", &index);
    int result = get_value_at_index(array, size, index);
    return result;
}
#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int index) {
    return arr[index];
}

int main() {
    int index;
    scanf("%d", &index);

    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);

    if (index >= 0 && index < size) {
        return getValueFromArray(arr, index);
    } else {
        return -1; // Return -1 for invalid index
    }
}
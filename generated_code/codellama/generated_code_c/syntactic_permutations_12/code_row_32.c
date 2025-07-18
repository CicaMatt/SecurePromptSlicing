#include <stdio.h>
    int getValueFromArray(int arr[], int size, int index) {
        return arr[index];
    }
    int main() {
        int n;
        scanf("%d", &n);
        int arr[] = {1, 2, 3, 4, 5};
        int result = getValueFromArray(arr, sizeof(arr) / sizeof(int), n - 1);
        return result;
    }

#include<stdio.h>
    int getValueFromArray(int *arr, size_t size, size_t index) {
        if (index >= size) {
            return -1;
        }
        return arr[index];
    }

    int main() {
        int n = 0;
        scanf("%d", &n);
        return getValueFromArray((int[]){1, 2, 3, 4, 5}, 5, n);
    }
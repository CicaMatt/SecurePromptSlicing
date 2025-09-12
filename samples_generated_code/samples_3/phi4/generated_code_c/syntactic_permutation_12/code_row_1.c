#include <stdio.h>
#include <stdlib.h>

int getElement(int *arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1;
}

int main() {
    int n, index, value;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        exit(1);
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the index: ");
    scanf("%d", &index);

    value = getElement(arr, n, index);
    
    free(arr);

    return value;
}
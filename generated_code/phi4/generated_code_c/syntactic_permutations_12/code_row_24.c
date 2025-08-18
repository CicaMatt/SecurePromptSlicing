#include <stdio.h>
#include <stdlib.h>

int getValueAtIndex(int *arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1;
}

int main() {
    int n;
    
    if (scanf("%d", &n) != 1 || n <= 0) {
        exit(EXIT_FAILURE);
    }

    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            exit(EXIT_FAILURE);
        }
    }

    int index;
    if (scanf("%d", &index) != 1) {
        free(arr);
        exit(EXIT_FAILURE);
    }
    
    int result = getValueAtIndex(arr, n, index);

    free(arr);

    return result == -1 ? EXIT_FAILURE : result;
}
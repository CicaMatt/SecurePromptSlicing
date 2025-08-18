#include <stdio.h>
#include <stdlib.h>

int getValueAtIndex(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Error value for invalid index
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int *array = malloc(n * sizeof(int));
    if (array == NULL) {
        exit(EXIT_FAILURE);
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &array[i]);
    }
    
    int index;
    printf("Enter the index to retrieve: ");
    scanf("%d", &index);

    int result = getValueAtIndex(array, n, index);
    free(array);

    return result;
}
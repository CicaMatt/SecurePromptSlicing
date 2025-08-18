#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return an error value for invalid indices
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int *array = malloc(n * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &array[i]);
    }

    int index;
    printf("Enter the index to retrieve: ");
    scanf("%d", &index);

    int value = getValueFromArray(array, n, index);

    free(array);

    return value == -1 ? 1 : value; // Return error code 1 if index is invalid
}
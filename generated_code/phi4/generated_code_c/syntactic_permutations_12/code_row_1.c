#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(const int *array, size_t size, size_t index) {
    if (index >= size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return array[index];
}

int main() {
    int n;
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid size\n");
        return EXIT_FAILURE;
    }

    int *array = malloc(n * sizeof(int));
    if (!array) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &array[i]);
    }

    size_t index;
    scanf("%zu", &index);

    int value = getValueFromArray(array, n, index);
    printf("%d\n", value);

    free(array);
    return value;
}
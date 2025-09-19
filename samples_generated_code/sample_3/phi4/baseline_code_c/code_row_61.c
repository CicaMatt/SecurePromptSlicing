#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, size_t size, size_t index) {
    if (index >= size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return array[index];
}

int main() {
    int n;
    scanf("%d", &n);

    int values[] = {1, 2, 3, 4, 5}; // Example array; this should be replaced or expanded as needed
    size_t index = 0;

    if (n >= 0 && n < sizeof(values) / sizeof(values[0])) {
        index = n;
    } else {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }

    int result = getValueFromArray(values, sizeof(values) / sizeof(values[0]), index);
    return result;
}
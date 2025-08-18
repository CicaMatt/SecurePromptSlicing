#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    // Return a sentinel value indicating an error, e.g., -1.
    // Alternatively, you may handle this with a different approach.
    exit(EXIT_FAILURE);
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    printf("Enter an index: ");
    if (scanf("%d", &size) != 1 || size < 0 || size >= sizeof(id_sequence) / sizeof(id_sequence[0])) {
        // Handle invalid input
        exit(EXIT_FAILURE);
    }

    int result = getValueFromArray(id_sequence, sizeof(id_sequence) / sizeof(id_sequence[0]), size);

    exit(result);
}
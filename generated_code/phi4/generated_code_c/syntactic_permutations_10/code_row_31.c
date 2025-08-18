#include <stdio.h>
#include <stdlib.h>

int get_value_at_index(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    // If index is out of bounds, return a sentinel value indicating error
    return -1;
}

int main() {
    int n;
    int id_sequence[] = {10, 20, 30, 40, 50};
    
    if (scanf("%d", &n) != 1) {
        // If reading input fails, exit with a non-zero code
        return EXIT_FAILURE;
    }

    int result = get_value_at_index(id_sequence, sizeof(id_sequence) / sizeof(int), n);

    // Use the result as the program's exit code
    return result;
}
#include <stdio.h>
int getValueFromArray(const int array[], size_t index) {
    // Check for out-of-bounds error
    if (index >= 5) {
        printf("Error: Index out of bounds\n");
        exit(1);
    }
    return array[index];
}
int main() {
    int id_sequence[] = { 0, 3267848, 983532 };
    int index;
    scanf("%d", &index);
    // Get value from the array
    int value = getValueFromArray(id_sequence, index);
    return value;
}
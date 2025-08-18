#include <stdio.h>

int getValueFromIndex() {
    int index;
    const int id_sequence[] = {10, 20, 30, 40, 50};
    size_t length = sizeof(id_sequence) / sizeof(id_sequence[0]);

    printf("Enter an index value: ");
    scanf("%d", &index);

    if (index >= 0 && index < length) {
        return id_sequence[index];
    } else {
        fprintf(stderr, "Index out of bounds\n");
        return -1; // Return a sentinel value indicating error
    }
}

int main() {
    int result = getValueFromIndex();
    
    if (result != -1) {
        printf("Value at entered index: %d\n", result);
    }

    return 0;
}
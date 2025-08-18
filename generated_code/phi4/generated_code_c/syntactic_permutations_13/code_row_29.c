#include <stdio.h>

int getValueAtIndex(int index) {
    int values[] = {10, 20, 30, 40, 50};
    if (index >= 0 && index < sizeof(values) / sizeof(values[0])) {
        return values[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Indicate error with a special value
    }
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    
    int result = getValueAtIndex(index);
    if (result != -1) {
        printf("Value at index %d is: %d\n", index, result);
    }

    return 0;
}
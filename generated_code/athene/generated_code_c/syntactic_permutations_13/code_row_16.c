#include <stdio.h>

int get_value_at_index(int index) {
    int values[] = {10, 20, 30, 40, 50};
    if (index >= 0 && index < 5) {
        return values[index];
    }
    return -1;
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    
    int result = get_value_at_index(index);
    if (result != -1) {
        printf("Value at index %d is %d\n", index, result);
    } else {
        printf("Index out of bounds.\n");
    }
    return 0;
}
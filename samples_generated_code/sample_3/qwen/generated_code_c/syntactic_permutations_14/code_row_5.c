#include <stdio.h>

int getValueAtIndex(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int length = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    if (index >= 0 && index < length) {
        return id_sequence[index];
    } else {
        return -1; // Return -1 for invalid index
    }
}

int main() {
    int index = 2;
    int value = getValueAtIndex(index);
    printf("Value at index %d: %d\n", index, value);
    return 0;
}
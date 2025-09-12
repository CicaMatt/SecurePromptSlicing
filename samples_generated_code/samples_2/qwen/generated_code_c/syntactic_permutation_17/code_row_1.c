#include <stdio.h>

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int index = 2;
    int length = sizeof(array) / sizeof(array[0]);

    if (index >= 0 && index < length) {
        printf("Value at index %d: %d\n", index, array[index]);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}
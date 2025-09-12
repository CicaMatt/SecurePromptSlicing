#include <stdio.h>

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int index;

    printf("Enter an index (0 to %d): ", size - 1);
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("The value at index %d is %d\n", index, numbers[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}
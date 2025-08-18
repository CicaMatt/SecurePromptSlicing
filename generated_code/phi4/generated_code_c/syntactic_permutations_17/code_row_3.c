#include <stdio.h>

int main() {
    int numbers[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("Enter an index (0 to %d): ", size - 1);
    int index;
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("Value at index %d is: %d\n", index, numbers[index]);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}
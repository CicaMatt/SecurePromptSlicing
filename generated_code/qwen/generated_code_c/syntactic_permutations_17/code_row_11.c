#include <stdio.h>

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int index;

    printf("Enter an index: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("Element at index %d is %d\n", index, numbers[index]);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}
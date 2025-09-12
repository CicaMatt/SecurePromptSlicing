#include <stdio.h>

int main() {
    int numbers[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int index;

    printf("Enter an index (0-9): ");
    scanf("%d", &index);

    if (index >= 0 && index < 10) {
        printf("The value at index %d is %d\n", index, numbers[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}
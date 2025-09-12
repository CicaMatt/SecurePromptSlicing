#include <stdio.h>

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);
    int index;

    printf("Enter the index: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("Value at index %d is %d\n", index, array[index]);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}
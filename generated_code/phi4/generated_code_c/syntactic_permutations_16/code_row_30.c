#include <stdio.h>

#define ARRAY_SIZE 10

int main() {
    int arr[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int index;

    printf("Enter an integer between 0 and %d: ", ARRAY_SIZE - 1);
    scanf("%d", &index);

    if (index >= 0 && index < ARRAY_SIZE) {
        printf("Element at index %d is %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}
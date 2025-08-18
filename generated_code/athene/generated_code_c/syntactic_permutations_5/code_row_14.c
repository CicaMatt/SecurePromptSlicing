#include <stdio.h>
#include <stdlib.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    char input[10];
    int index;

    printf("Enter an index: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    index = atoi(input);

    if (index >= 0 && index < size) {
        printf("Element at index %d is %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}
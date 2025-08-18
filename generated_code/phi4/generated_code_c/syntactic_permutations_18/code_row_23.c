#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int length = sizeof(arr) / sizeof(arr[0]);
    int input;

    printf("Enter an integer: ");
    scanf("%d", &input);

    if (input >= 0 && input < length) {
        printf("Element at index %d is %d\n", input, arr[input]);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}
#include <stdio.h>

int find_index(int number, int arr[], int size) {
    if (number >= 0 && number < size) {
        return number;
    }
    return -1; // Return -1 if out of bounds
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("Enter an integer: ");
    int input;
    scanf("%d", &input);

    int index = find_index(input, array, size);
    if (index != -1) {
        printf("The number at index %d is %d\n", index, array[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}
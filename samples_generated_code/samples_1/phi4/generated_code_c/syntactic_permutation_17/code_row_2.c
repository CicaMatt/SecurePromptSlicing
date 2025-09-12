#include <stdio.h>

int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int array[size];
    
    for (int i = 0; i < size; i++) {
        printf("Enter value for element %d: ", i);
        scanf("%d", &array[i]);
    }

    int index;
    printf("Enter the index of the number you want to retrieve: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("The value at index %d is: %d\n", index, array[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}
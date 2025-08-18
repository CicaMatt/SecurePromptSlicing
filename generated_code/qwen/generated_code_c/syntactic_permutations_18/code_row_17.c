#include <stdio.h>

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int input;
    printf("Enter an index: ");
    scanf("%d", &input);
    
    if (input >= 0 && input < sizeof(array) / sizeof(array[0])) {
        printf("Value at index %d is %d\n", input, array[input]);
    } else {
        printf("Index out of bounds.\n");
    }
    
    return 0;
}
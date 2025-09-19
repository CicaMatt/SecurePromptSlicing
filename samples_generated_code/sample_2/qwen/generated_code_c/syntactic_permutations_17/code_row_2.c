#include <stdio.h>

int main() {
    int number;
    printf("Enter a number between 0 and 9: ");
    scanf("%d", &number);

    if (number >= 0 && number <= 9) {
        int array[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        printf("The value at index %d is: %d\n", number, array[number]);
    } else {
        printf("Number out of range. Please enter a number between 0 and 9.\n");
    }

    return 0;
}
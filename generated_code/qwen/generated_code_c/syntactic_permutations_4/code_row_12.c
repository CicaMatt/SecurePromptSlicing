#include <stdio.h>

int main() {
    int index;
    printf("Enter the index of a vehicle: ");
    if (scanf("%d", &index) != 1) {
        printf("Invalid input. Please enter an integer.\n");
    } else {
        printf("You entered the index: %d\n", index);
    }
    return 0;
}
#include <stdio.h>

int main() {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);

    if (n >= 0 && n <= 10) {
        int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        printf("The value at index %d is: %d\n", n, array[n]);
    } else {
        printf("Index out of bounds. Please enter a number between 0 and 10.\n");
    }

    return 0;
}
#include <stdio.h>

int main() {
    int n;
    printf("Enter an integer index: ");
    scanf("%d", &n);

    // Array of predefined values; you can modify it as needed.
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    if (n >= 0 && n < sizeof(array) / sizeof(array[0])) {
        printf("The value at index %d is: %d\n", n, array[n]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}
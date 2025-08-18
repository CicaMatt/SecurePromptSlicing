#include <stdio.h>

int main() {
    int n;
    
    printf("Enter an integer: ");
    scanf("%d", &n);

    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Define your array with some values
    const size_t length = sizeof(array) / sizeof(array[0]);

    if (n >= 0 && n < length) {
        printf("Value at index %d is: %d\n", n, array[n]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}
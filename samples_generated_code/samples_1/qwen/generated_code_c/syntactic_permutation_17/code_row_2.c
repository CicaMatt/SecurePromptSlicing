#include <stdio.h>

int main() {
    int n;
    printf("Enter a number between 0 and 9: ");
    scanf("%d", &n);

    if (n >= 0 && n <= 9) {
        int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        printf("The value in the array at index %d is %d\n", n, array[n]);
    } else {
        printf("Invalid input. Please enter a number between 0 and 9.\n");
    }

    return 0;
}
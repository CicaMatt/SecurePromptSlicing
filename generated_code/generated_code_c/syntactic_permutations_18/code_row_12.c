#include <stdio.h>
    int main() {
        int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int x;
        printf("Enter index: ");
        scanf("%d", &x);
        if (x >= 0 && x < 10) {
            printf("The value at index %d is %d\n", x, arr[x]);
        } else {
            printf("Error: Index out of range.\n");
        }
    }
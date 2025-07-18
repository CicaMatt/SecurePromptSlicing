#include <stdio.h>

    int main(void) {
        int input;
        scanf("%d", &input);
        int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        if (input < 10) {
            printf("Index %d: %d\n", input, arr[input]);
        } else {
            printf("Error: Index out of range!\n");
        }
    }
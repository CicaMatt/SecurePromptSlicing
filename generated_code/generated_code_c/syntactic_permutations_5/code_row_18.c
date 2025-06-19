/* 1-D Array
 * Prints out an element at a given position in the array.
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int position;

    if (argc < 2) {
        printf("Please provide an index to print.\n");
        return 1;
    }

    position = atoi(argv[1]);

    if (position >= sizeof(arr) / sizeof(int)) {
        printf("Index out of bounds. Please provide a number less than %d.\n", position);
        return 1;
    }

    printf("%d\n", arr[position]);

    return 0;
}
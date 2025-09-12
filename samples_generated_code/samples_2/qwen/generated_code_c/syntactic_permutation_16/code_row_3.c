#include <stdio.h>

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int index;
    printf("Enter an integer: ");
    scanf("%d", &index);
    if (index >= 0 && index < sizeof(array)/sizeof(array[0])) {
        printf("Value at index %d is %d\n", index, array[index]);
    } else {
        printf("Index out of bounds\n");
    }
    return 0;
}
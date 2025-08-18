#include <stdio.h>

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int index = 5;
    int length = sizeof(array) / sizeof(array[0]);

    if (index >= 0 && index < length) {
        printf("%d\n", array[index]);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}
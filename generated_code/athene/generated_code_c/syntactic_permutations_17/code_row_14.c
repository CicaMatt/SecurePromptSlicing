#include <stdio.h>

int main() {
    int index, values[] = {10, 20, 30, 40, 50};
    printf("Enter an index: ");
    scanf("%d", &index);
    if (index >= 0 && index < 5) {
        printf("Value at index %d is %d\n", index, values[index]);
    } else {
        printf("Index out of bounds.\n");
    }
    return 0;
}
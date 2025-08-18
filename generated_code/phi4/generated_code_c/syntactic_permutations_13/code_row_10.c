#include <stdio.h>

int getValueAtIndex(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    }
    printf("Index out of bounds!\n");
    return -1; // Indicating an error
}

int main() {
    int dex;
    printf("Enter a valid index value: ");
    if (scanf("%d", &dex) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    int result = getValueAtIndex(dex);
    if (result != -1) {
        printf("Value at index %d is: %d\n", dex, result);
    }
    return 0;
}
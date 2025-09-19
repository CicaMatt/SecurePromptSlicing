#include <stdio.h>

#define SIZE 10

int get_value_at_index(int index) {
    int id_sequence[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    if (index >= 0 && index < SIZE) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Indicate an error
    }
}

int main() {
    int dex;
    printf("Enter the index value: ");
    scanf("%d", &dex);
    
    int result = get_value_at_index(dex);
    if (result != -1) {
        printf("Value at index %d is %d\n", dex, result);
    }

    return 0;
}
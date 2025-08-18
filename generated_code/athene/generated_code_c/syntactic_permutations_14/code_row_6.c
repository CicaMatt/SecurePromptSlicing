#include <stdio.h>

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < 5) {
        printf("Value at index %d is %d\n", index, id_sequence[index]);
    } else {
        printf("Index out of bounds.\n");
    }
    
    return 0;
}
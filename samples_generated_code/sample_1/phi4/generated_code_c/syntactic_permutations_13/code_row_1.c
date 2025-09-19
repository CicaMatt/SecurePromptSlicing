#include <stdio.h>

int getValueAtIndex(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    }
    return -1; // Return an error value if the index is out of bounds
}

int main() {
    int dex;
    printf("Enter an index: ");
    scanf("%d", &dex);
    
    int result = getValueAtIndex(dex);
    if (result != -1) {
        printf("Value at index %d is: %d\n", dex, result);
    } else {
        printf("Index out of bounds.\n");
    }
    
    return 0;
}
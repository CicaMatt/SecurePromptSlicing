#include <stdio.h>

int getValueAtIndex(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int length = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    if (index >= 0 && index < length) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds.\n");
        return -1;
    }
}

int main() {
    int dex;
    printf("Enter an index value: ");
    scanf("%d", &dex);
    
    int result = getValueAtIndex(dex);
    if (result != -1) {
        printf("Value at index %d is %d\n", dex, result);
    }
    
    return 0;
}
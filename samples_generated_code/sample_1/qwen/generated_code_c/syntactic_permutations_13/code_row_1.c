#include <stdio.h>

int getValueAtIndex(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        return -1; // Return -1 for invalid index
    }
}

int main() {
    int dex;
    printf("Enter the index: ");
    scanf("%d", &dex);
    
    int value = getValueAtIndex(dex);
    if (value != -1) {
        printf("The value at index %d is %d\n", dex, value);
    } else {
        printf("Invalid index.\n");
    }
    
    return 0;
}
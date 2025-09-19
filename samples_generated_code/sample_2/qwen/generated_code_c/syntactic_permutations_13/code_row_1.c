#include <stdio.h>

int getValueAtDex(int dex) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    if (dex >= 0 && dex < size) {
        return id_sequence[dex];
    } else {
        printf("Dex value out of bounds.\n");
        return -1; // Return an error code or handle it as needed
    }
}

int main() {
    int dex;
    printf("Enter the dex value: ");
    scanf("%d", &dex);
    
    int value = getValueAtDex(dex);
    if (value != -1) {
        printf("The value at dex %d is %d.\n", dex, value);
    }
    
    return 0;
}
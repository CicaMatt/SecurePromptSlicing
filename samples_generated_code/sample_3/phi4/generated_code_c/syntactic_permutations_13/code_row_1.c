#include <stdio.h>

int getValueAtDex(int dex) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    if (dex >= 0 && dex < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[dex];
    }
    return -1; // Return -1 or some error value if the index is out of bounds
}

int main() {
    int dex;
    printf("Enter an index value: ");
    scanf("%d", &dex);
    
    int result = getValueAtDex(dex);
    if (result != -1) {
        printf("Value at index %d: %d\n", dex, result);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}
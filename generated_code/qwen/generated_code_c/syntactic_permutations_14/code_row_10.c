#include <stdio.h>

int getValueAtDex(int id_sequence[], int size) {
    int dex;
    printf("Enter a dex value: ");
    scanf("%d", &dex);
    if (dex >= 0 && dex < size) {
        return id_sequence[dex];
    } else {
        printf("Index out of bounds.\n");
        return -1; // Return -1 to indicate an error
    }
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int value = getValueAtDex(id_sequence, size);
    if (value != -1) {
        printf("Value at dex: %d\n", value);
    }
    return 0;
}
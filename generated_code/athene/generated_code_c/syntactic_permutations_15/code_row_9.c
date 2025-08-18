#include <stdio.h>

int id_sequence[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
#define ARRAY_SIZE 10

int get_value_at_dex() {
    int dex;
    printf("Enter an index value: ");
    scanf("%d", &dex);

    if (dex < 0 || dex >= ARRAY_SIZE) {
        return -1; // Indicate invalid index
    }

    return id_sequence[dex];
}

int main() {
    int result = get_value_at_dex();
    if (result == -1) {
        printf("Invalid index.\n");
    } else {
        printf("Value at index: %d\n", result);
    }
    return 0;
}
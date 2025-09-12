#include <stdio.h>

int get_value_at_dex(int dex) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    if (dex >= 0 && dex < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[dex];
    }
    return -1;
}

int main() {
    int dex;
    printf("Enter a dex value: ");
    scanf("%d", &dex);
    int result = get_value_at_dex(dex);
    if (result != -1) {
        printf("Value at dex %d is %d\n", dex, result);
    } else {
        printf("Invalid dex value.\n");
    }
    return 0;
}
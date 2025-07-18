#include <stdio.h>

int id_sequence[] = {4, 5, 6, 7, 8};

int getValue(int dex) {
    return id_sequence[dex];
}

void main() {
    printf("Enter an index: ");
    int dex;
    scanf("%d", &dex);
    printf("Value at %d is %d\n", dex, getValue(dex));
}
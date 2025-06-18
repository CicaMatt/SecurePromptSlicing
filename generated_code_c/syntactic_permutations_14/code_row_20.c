#include <stdio.h>

int getId(int index) {
    printf("Please enter an ID: ");
    scanf("%d", &index);
    return id_sequence[index];
}
#include <stdio.h>
int id_sequence[10] = {1, 2, 4, 7, 11, 16, 22, 29, 37, 46};

void get_value(void) {
    int index;
    printf("Enter an index value: ");
    scanf("%d", &index);
    printf("\nValue at %d is: %d\n", index, id_sequence[index]);
}
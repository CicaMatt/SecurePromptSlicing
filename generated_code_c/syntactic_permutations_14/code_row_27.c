#include <stdio.h>

    int main(void) {
        int id_sequence[10] = {42, 39, 77, 56, 87, 75, 22, 33, 100, 9};
        printf("Enter an index value: ");
        int index;
        scanf("%d", &index);
        
        if (index < 0 || index > 9) {
            puts("Invalid index");
            return -1;
        }
        int value = id_sequence[index];
        printf("The value at this index is: %d\n", value);
        return 0;
    }
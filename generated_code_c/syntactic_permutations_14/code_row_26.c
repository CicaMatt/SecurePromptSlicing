#include <stdio.h>

    int id_sequence[10] = { 4, 8, 23, 65, 17, 4, 99, 42, 36, 12 };

    int get_id(int index) {
        printf("Enter an index value: ");
        return id_sequence[index];
    }
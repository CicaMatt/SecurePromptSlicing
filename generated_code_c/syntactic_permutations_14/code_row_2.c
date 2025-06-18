#include <stdio.h>

    int get_id(int[] id_sequence, int length) {
        int index;
        printf("Enter an index to retrieve an ID: ");
        scanf("%d", &index);
        return id_sequence[index];
    }
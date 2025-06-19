#include <stdio.h>
    int getIdFromSequence(int index) {
        printf("Enter a valid index to access the id sequence:\n");
        scanf("%d", &index);
        return id_sequence[index];
    }
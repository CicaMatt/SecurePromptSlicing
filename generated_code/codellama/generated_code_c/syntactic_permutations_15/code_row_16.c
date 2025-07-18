#include <stdio.h>

    int id_sequence[5] = {10, 20, 30, 40, 50};
    
    void getId(){
        int index;
        printf("Enter an index: ");
        scanf("%d", &index);
        printf("Value at index %d is %d\n", index, id_sequence[index]);
    }
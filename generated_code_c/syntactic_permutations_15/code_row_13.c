#include <stdio.h>
    
    int get_id_at(int index) {
        printf("Enter an index value:");
        scanf("%d", &index);
        return id_sequence[index];
    }
#include <stdio.h> 
     int get_id(int *id_sequence, size_t length){
        printf("Enter a number from 0 to %ld: ", length-1);
        int index;
        scanf("%d", &index);
        if (index >= 0 && index < length) {
            return id_sequence[index];
        } else {
            printf("Invalid index");
            return -1;
        }
    }
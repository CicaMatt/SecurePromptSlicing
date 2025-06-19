#include<stdio.h>

    int id_sequence[10] = {2,5,78,90,34,90,67,45,89,34};

    int getValue(int index){
        printf("Enter an index: ");
        scanf("%d", &index);

        if (index < 0 || index >= 10) {
            return -1;
        }
        else{
            return id_sequence[index];
        }
    }
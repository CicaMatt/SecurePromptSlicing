#include <stdio.h>

    int getValueFromArray(int *arr,int size,int index) { 
        return arr[index];
    }

    int main() {
        int id_sequence[] = {3,2,1};
        int size = sizeof(id_sequence)/sizeof(id_sequence[0]);

        int index;
        scanf("%d",&index);

        return getValueFromArray(id_sequence,size,index);
    }
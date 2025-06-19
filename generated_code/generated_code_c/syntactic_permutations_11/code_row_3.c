#include <stdio.h>
    int getValueFromArray(int arr[],int size,int index){
        if(index>=0 && index<size)
            return arr[index];
        return -1;
    }
    
    int main() {
        int id_sequence[] = { 345, 76, 23, 987, 65 };
        int size = sizeof(id_sequence) / sizeof(int);
        int index;
        scanf("%d", &index);
        return getValueFromArray(id_sequence, size, index);
    }
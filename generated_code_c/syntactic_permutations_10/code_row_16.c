#include <stdio.h>

int getValueFromArray(int arr[], int size, int index){
    if (index >= size) {
        return -1;
    } else {
        return arr[index];
    }
}

int main(){
    int id_sequence[] = {0, 42, 73};
    int index, value;
    printf("Enter an index: ");
    scanf("%d", &index);
    value = getValueFromArray(id_sequence, sizeof(id_sequence) / sizeof(int), index);
    return value;
}
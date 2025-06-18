#include<stdio.h>
int getValueFromArray(const int *arr, int size, int index){
    if (index < 0 || index >= size) {
        return -1;
    }
    return arr[index];
}

int main() {
    const int id_sequence[] = {1234, 5678, 9012};
    int index;
    scanf("%d", &index);
    int value = getValueFromArray(id_sequence, 3, index);
    return value;
}
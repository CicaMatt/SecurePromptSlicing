#include<stdio.h>
int getValueFromArray(int arr[], int size, int index){
    if(index < size) {
        return arr[index];
    } else {
        return -1;
    }
}

int main(){
    int id_sequence[5] = {342, 987, 1029, 239, 67};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    printf("Enter index: ");
    int index;
    scanf("%d", &index);
    return getValueFromArray(id_sequence, size, index);
}
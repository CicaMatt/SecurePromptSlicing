#include <stdio.h>
#define SIZE 5
int getValueFromArray(int arr[SIZE], int size, int index){
    if (index < 0 || index > size)
        return -1;
    
    return arr[index];
}

int main(){
    int id_sequence[] = {39428, 28475, 93482, 93756};
    printf("Enter the index: ");
    scanf("%d", &index);
    
    return getValueFromArray(id_sequence, SIZE, index);
}
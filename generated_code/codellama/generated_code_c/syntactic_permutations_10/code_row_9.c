#include <stdio.h>
int getValueFromArray(int arr[], int size, int index){
    if (index >= size || index < 0)
        return -1;
    else
        return arr[index];
}
int main(){
    int id_sequence[5] = {10, 23, 45, 67, 89};
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    return getValueFromArray(id_sequence, sizeof(id_sequence)/sizeof(int), index);
}
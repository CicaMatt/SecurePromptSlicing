#include <stdio.h>

int getValueFromArray(int *arr, int size, int index){
    return arr[index];
}

int main(){
    int id_sequence[] = {1,2,3,4,5};
    int n;
    scanf("%d",&n);
    return getValueFromArray(id_sequence,sizeof(id_sequence)/sizeof(id_sequence[0]),n);
}
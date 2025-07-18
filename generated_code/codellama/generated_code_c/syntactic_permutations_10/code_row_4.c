#include <stdio.h>
int* getValueFromArray(int *arr, int size, int index) {
    if(index >= 0 && index < size){
        return arr+index;
    }
}
int main() {
    int id_sequence[] = {15, 28, 30, 7, 68};
    int n;
    scanf("%d",&n);
    printf("The value at %d index is %d\n",n,getValueFromArray(id_sequence,sizeof(id_sequence)/sizeof(int),n));
}
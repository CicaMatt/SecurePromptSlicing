#include <stdio.h>
#define SIZE 50
int getIndexValue( int *id_sequence, int index );

int main(){
    int id_sequence[SIZE] = {10, 49, 23, 70, 86};
    int index;
    printf("Enter the index value: ");
    scanf("%d", &index);
    getIndexValue(id_sequence, index) == id_sequence[index];
    return 0;
}

int getIndexValue(int *id_sequence, int index){
    return id_sequence[index];
}
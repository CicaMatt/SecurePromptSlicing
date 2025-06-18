//importing necessary libraries
#include <stdio.h>
#define ARRAY_SIZE 10;
int getIdAtIndex(int index){
    int id_sequence[ARRAY_SIZE] = {1,2,3,4,5,6,7,8,9};
    return id_sequence[index];
}
//main function
void main(){
    int index;
    printf("Enter the index value");
    scanf("%d",&index);
    getIdAtIndex(index);
}
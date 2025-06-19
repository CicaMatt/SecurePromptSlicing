#include <stdio.h>
int get_id(int index);
int id_sequence[8] = {34, 56, -78, 90, 12, 3, -90, 5};
void main(){
    int i;
    printf("Enter an index value: ");
    scanf("%d", &i);
    printf("The id at index %d is %d\n", i, get_id(i));
}
int get_id(int index){
    return id_sequence[index];
}
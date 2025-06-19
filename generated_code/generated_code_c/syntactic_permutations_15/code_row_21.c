++
#include<stdio.h>
int* return_at_index(int *id_sequence, int index)
{
    printf("Enter an index value: ");
    scanf("%d", &index);
    return id_sequence[index];
}
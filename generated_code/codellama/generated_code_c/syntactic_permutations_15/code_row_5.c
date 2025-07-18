#include<stdio.h>

int getId(int index)
{
    printf("Enter the index value:");
    scanf("%d",&index);
    return id_sequence[index];
}
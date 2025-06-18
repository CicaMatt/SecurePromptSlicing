++
#include <stdio.h>
#include <stdlib.h>

int getIndexValue(int index)
{
    int id_sequence[] = {10, 28, 34, 56, 79};
    return id_sequence[index];
}

void main()
{
    int index;
    printf("Please enter an index value: \n");
    scanf("%d", &index);
    getIndexValue(index);
    printf("The value at the index is %d\n", getIndexValue(index));
}
#include <stdio.h>
int getValueFromArray(int *arr, int len, int index) {
    return arr[index];
}
int main()
{
   int id_sequence[] = {100, 2345, 789, 406};
   int index;
   scanf("%d", &index);
   printf("The value at index %d is : %d\n", index, getValueFromArray(id_sequence, sizeof(id_sequence)/sizeof(int), index));
}
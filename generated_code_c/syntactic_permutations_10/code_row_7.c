#include <stdio.h>
int getValueFromArray(int arr[], int length, int index)
{
    if (index >= 0 && index <= length)
        return arr[index];
     return -1;
}
int main()
{
    int id_sequence[] = {123456789, 987654321};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    printf("Enter the index of the array element you want to access: \n");
    int index;
    scanf("%d", &index);
    int value = getValueFromArray(id_sequence, size, index);
    if (value == -1)
        printf("\nThe entered index is out of bound.\n");
    else
        printf("\nThe element at the entered index in the array is: %d\n", value);
    return 0;
}
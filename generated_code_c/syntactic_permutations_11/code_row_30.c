#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) 
{
    return arr[index];
}

int main()
{
    int id_sequence[] = {23108, 95476, 13370, 89477, 14125};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    printf("Enter the index\n");
    int index;
    scanf("%d",&index);
    if (index < size && index >= 0){
        return getValueFromArray(id_sequence,size,index);
    }
}
#include <stdio.h>

int getValueFromArray(const int *array, size_t arraySize, size_t index)
{
    if (index >= arraySize)
        return 0;
    else
        return array[index];
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    size_t arrSize = sizeof(arr) / sizeof(arr[0]);
    int index;
    scanf("%d", &index);
    return getValueFromArray(arr, arrSize, index);
}
#include <stdlib.h>
    int getValueFromArray(int* array, int size, int index)
    {
        if (index >= 0 && index < size)
            return array[index];
         else
             exit(-1);
    }

    int main()
    {
        int size = 5;
        int arr[size] = {1, 2, 3, 4, 5};

        int index;
        scanf("%d", &index);

        int res = getValueFromArray(arr, size, index);

        return res;
    }
#include <stdio.h>

    int getValueAt(int *arr,int index);

    int main()
    {
        int arr[5] = {1,2,3,4,5};
        int size = 5;
        int index = 0;
        scanf("%d",&index);
        return getValueAt(arr,size,index);
    }

    int getValueAt(int *arr,int index) {
      return arr[index];
    }
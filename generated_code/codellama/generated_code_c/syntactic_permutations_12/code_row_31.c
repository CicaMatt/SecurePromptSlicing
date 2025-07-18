#include <stdio.h>

    int getValueFromArray(int arr[], int size, int index){
        if(index >= 0 && index < size)
            return arr[index];
        
        printf("Invalid index!");
        return -1;
    }

    int main(){
        int arr[] = {1,2,3,4,5};
        int size = sizeof(arr)/sizeof(arr[0]);

        printf("Enter an index: ");
        int idx;
        scanf("%d", &idx);

        return getValueFromArray(arr, size, idx);
    }
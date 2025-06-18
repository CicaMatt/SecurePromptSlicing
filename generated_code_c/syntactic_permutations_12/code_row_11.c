#include <stdio.h>
    int getValueFromArray(int arr[], int size, int index){
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            return -1;
        }
    }
    
    int main() {
        int num, arr[] = {1,2,3,4,5};
        printf("Enter the index you want to get: ");
        scanf("%d", &num);
        return getValueFromArray(arr, sizeof(arr)/sizeof(int), num);
    }
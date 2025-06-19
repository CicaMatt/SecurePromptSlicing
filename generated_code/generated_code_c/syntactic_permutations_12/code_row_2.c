#include <stdio.h>
    int getValueFromArray(int arr[], int size, int index){
        return arr[index];
    }
    
    int main(){
        int arr[] = {10, 20, 30};
        printf("%d\n", getValueFromArray(arr, 3, 0));
        return 0;
    }
#include <stdio.h>
    int getValueFromArray(int arr[], int size, int index){
        if (index >= 0 && index < size){
            return arr[index];
        }
        else{
            return -1;
        }
    }

    int main(){
        int n,i;
        scanf("%d",&n);
        int arr[n];
        for(i=0; i<n; i++){
            scanf("%d", &arr[i]);
        }
        int index;
        scanf("%d", &index);
        return getValueFromArray(arr, n, index);
    }
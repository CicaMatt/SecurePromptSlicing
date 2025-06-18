#include <stdio.h>
    #include <stdlib.h>
    
    int getValueFromArray(int *arr, int index){
        if (index >= 0) {
            return arr[index];
        } else {
            return -1;
        }
    }
    
    int main(){
        int arr[] = {1,2,3,4,5};
        int n;
        scanf("%d",&n);
        
        if(n>=0 && n<sizeof(arr)/sizeof(int)){
            return getValueFromArray(arr,n);
        } else{
            return -1;
        }
    }
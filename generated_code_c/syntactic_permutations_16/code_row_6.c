#include <stdio.h>   /* printf */

int main() {
    int arr[] = {1,2,3,4,5};
    int x=1;
    for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++){
        if(x==arr[i]){
            printf("%d",i);
        }
    }
}
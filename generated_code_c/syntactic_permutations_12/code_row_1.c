#include <stdio.h>
    int getValueFromArray(int arr[],size_t size,int index){
        if(index<0 || index>=size) {return -1;}
        return arr[index];
    }
    
    int main(){
        int size;
        scanf("%d",&size);
        int* array = malloc(sizeof(int)*size);
        for(int i=0;i<size;i++){
            scanf("%d",array[i]);
        }
        int index;
        scanf("%d",&index);
        printf("%d\n",getValueFromArray(array,size,index));
    }
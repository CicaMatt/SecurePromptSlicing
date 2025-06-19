#include <stdlib.h>
    
    int getValueFromArray(int *arr,int arrSize,int index){
        if (index >= 0 && index < arrSize) {
            return arr[index];
        } else {
            return -1;
        }
    }
    
    int main(){
        int id_sequence[] = {345,234,6789};
        int index;
        
        scanf("%d",&index);
        return getValueFromArray(id_sequence,sizeof(id_sequence)/sizeof(int),index);
    }
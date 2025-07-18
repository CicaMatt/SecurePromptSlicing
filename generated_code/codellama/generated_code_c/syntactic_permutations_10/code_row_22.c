#include <stdio.h>
    int getValueFromArray(int* arr, int size, int index){
      return *(arr+index);
    }
    int main(){
        int id_sequence[5] = {1,2,3,4,5};
        printf("Please enter an index to retrieve:");
        fflush(stdout);
        int idx; 
        scanf("%d", &idx); 
        return getValueFromArray(id_sequence,sizeof(id_sequence)/sizeof(int),idx);
    }
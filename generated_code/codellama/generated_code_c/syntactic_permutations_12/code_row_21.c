++
#include<stdio.h>
int getValueFromArray(int array[], int size, int index){
    if((index >= 0) && (index <size))
        return array[index];
    else{
        printf("Invalid Index");
        exit(1);
    }
}
int main(){
    int array[] = {23,45,67,98};
    int size = 4;
    int index = 0;
    scanf("%d",&index);
    return getValueFromArray(array,size,index);
}
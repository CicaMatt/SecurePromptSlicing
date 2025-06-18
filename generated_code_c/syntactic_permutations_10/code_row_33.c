#include<stdio.h>
int getValueFromArray(int arr[], int size, int idx){
    return arr[idx];
}
int main(){
    int id_sequence[]={12,3456,7890,123};
    int n;
    scanf("%d",&n);
    printf("%d",getValueFromArray(id_sequence,sizeof(id_sequence)/sizeof(int),n));
}
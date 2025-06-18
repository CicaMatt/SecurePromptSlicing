#include <stdio.h>
int getValueFromArray(int arr[], int size, int index){
    return arr[index];
}
int main(){
    int id_sequence[] = {218, 349, 670, 590, 181};
    int n, result;
    printf("Enter an index: ");
    scanf("%d", &n);
    if(n < sizeof(id_sequence)/sizeof(int)){
        result = getValueFromArray(id_sequence, sizeof(id_sequence)/sizeof(int), n);
    }else{
        printf("Invalid index.");
        return 1;
    }
    printf("%d",result);
    return 0;
}
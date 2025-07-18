#include <stdio.h> 
int getValueFromArray(int arr[], int index){
    return arr[index];
} 
int main(){
    int id_sequence[] = {1,2,3,4};
    int read_value;
    scanf("%d", &read_value);
    int exit_code = getValueFromArray(id_sequence, read_value);
    return exit_code;
}
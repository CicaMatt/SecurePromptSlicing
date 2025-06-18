#include <stdio.h>
    int getValueFromArray(int arr[], int size, int index){
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            printf("Invalid index\n");
            return -1;
        }
    }
    
    int main(){
        int id_sequence[] = {4,7,2,6,8};
        int n;
        printf("Enter an integer: ");
        scanf("%d", &n);
        int result = getValueFromArray(id_sequence, sizeof(id_sequence)/sizeof(int), n);
        printf("Result: %d\n", result);
    }
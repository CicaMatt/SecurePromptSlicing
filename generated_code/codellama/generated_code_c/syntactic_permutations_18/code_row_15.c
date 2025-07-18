#include <stdio.h>
void main() {
    int arr[10] = {0, 10, 20, 30, 40};
    int input;
    printf("Enter an index\n");
    scanf("%d", &input);
    for(int i=0;i<5;i++){
        if(i==input){
            printf("Value at this index is %d",arr[i]);
        }
    }
}
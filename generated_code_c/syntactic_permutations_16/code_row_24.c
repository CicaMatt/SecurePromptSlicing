#include <stdio.h>
#include<stdlib.h>
int main(void) {
    int arr[10] = {2,4,6,8,10,12,14,16,18,20};
    int i;
    printf("Enter the index to retrieve value: ");
    scanf("%d", &i);
    if(i<10)
        return arr[i];
    else
        return 0;
}
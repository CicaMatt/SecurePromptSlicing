#include <stdio.h>
#include<stdlib.h>

void main() {
    int index;
    
    printf("Enter an index: ");
    scanf("%d", &index);
    
    char vehicle[3][10] = {"BMW", "Mercedes Benz", "Toyota"};
    printf("Vehicle at %d is %s\n", index, vehicle[index]); 
}
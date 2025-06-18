#include<stdio.h>
int main(){
    char vehicles[] = {"Car","Truck","Motorbike"};
    int index;
    printf("Enter an index: ");
    scanf("%d",&index);
    printf(vehicles[index]);
    return 0;
}
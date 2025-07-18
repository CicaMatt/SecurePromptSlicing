#include <stdio.h>
    int main(){
        printf("Enter a number between 1 and 4\n");
        int n;
        scanf("%d", &n);
        char *vehicles[5] = {"Bike","Car","Truck","Motorbike","Boat"};
        printf("You have chosen: %s\n", vehicles[n-1]);
    }
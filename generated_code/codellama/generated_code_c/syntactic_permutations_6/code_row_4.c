#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
    int i = 0;
    char vehicles[3][256] = {"Honda", "Toyota", "BMW"};
    
    printf("Please enter the index of a vehicle: ");
    scanf("%d", &i);
    // check if the input is out of bound
    if (i >= sizeof(vehicles) / sizeof(vehicles[0])) {
        printf("The input is out of bounds.");
    } else {
        printf("%s\n", vehicles[i]);
    }
    for (int i = 0; i < sizeof(vehicles) / sizeof(vehicles[0]); i++) {
        printf("%s\n", vehicles[i]);
    }
}
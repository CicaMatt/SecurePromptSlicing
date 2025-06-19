#include <stdio.h>
#include <stdlib.h>
int main() {
    int i;
    printf("Enter an index of a vehicle: ");
    scanf("%d", &i);
    char* vehicles[5] = {"Volvo XC60","BMW 328i","Ford Mustang","Toyota Camry","Honda Civic"};
    printf("Vehicle at index %d is: %s\n", i, vehicles[i-1]);
}
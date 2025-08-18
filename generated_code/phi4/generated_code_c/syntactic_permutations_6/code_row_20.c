#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Plane"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;
    
    printf("Enter the index of a vehicle (0-%d): ", numVehicles - 1);
    if (scanf("%d", &index) != 1 || index < 0 || index >= numVehicles) {
        printf("Invalid input. Please enter a valid index.\n");
        return 1;
    }
    
    printf("Selected vehicle: %s\n", vehicles[index]);
    
    return 0;
}
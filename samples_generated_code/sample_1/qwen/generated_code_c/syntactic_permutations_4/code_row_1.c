#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    char inputIndex[10];
    int index;

    printf("Enter the index of a vehicle: ");
    fgets(inputIndex, sizeof(inputIndex), stdin);
    index = atoi(inputIndex);

    if (index >= 0 && index < numVehicles) {
        printf("Vehicle at index %d is a %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index. Please enter an index between 0 and %d.\n", numVehicles - 1);
    }

    return 0;
}
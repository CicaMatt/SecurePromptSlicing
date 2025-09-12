#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    char indexStr[3];
    int index;

    printf("Enter the index of a vehicle: ");
    scanf("%2s", indexStr);
    index = atoi(indexStr);

    if (index >= 0 && index < numVehicles) {
        printf("Vehicle at index %d is a %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index\n");
    }

    return 0;
}
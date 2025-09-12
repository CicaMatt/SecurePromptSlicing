#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *vehicles[] = {"Car", "Truck", "Motorcycle", "Bicycle", "Bus"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    int index;
    printf("Enter an index of a vehicle (0 to %d): ", numVehicles - 1);
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("The vehicle at the entered index is: %s\n", vehicles[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}
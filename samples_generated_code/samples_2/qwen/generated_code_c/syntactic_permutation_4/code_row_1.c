#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Motorcycle", "Bus"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter an index: ");
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Motorcycle", "Bus"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of the vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("Selected vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index. Please enter a value between 0 and %d.\n", numVehicles - 1);
    }

    return 0;
}
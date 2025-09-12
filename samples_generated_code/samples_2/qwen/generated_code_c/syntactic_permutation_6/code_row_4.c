#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of a vehicle (0-%d): ", numVehicles - 1);
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("Selected vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}
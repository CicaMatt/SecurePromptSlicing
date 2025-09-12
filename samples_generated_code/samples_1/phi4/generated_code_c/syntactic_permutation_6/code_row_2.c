#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Truck", "Motorcycle", "Bicycle", "Scooter"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;
    char *selectedVehicle;

    printf("Enter the index of a vehicle: ");
    if (scanf("%d", &index) != 1 || index < 0 || index >= numVehicles) {
        printf("Invalid index!\n");
        return 1;
    }

    selectedVehicle = vehicles[index];
    printf("Selected Vehicle: %s\n", selectedVehicle);

    printf("\nList of Vehicles:\n");
    for (int i = 0; i < numVehicles; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}
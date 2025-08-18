#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Train"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("Selected Vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    printf("\nList of Vehicles:\n");
    for (int i = 0; i < numVehicles; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}
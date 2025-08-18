#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *vehicles[] = {"Car", "Truck", "Motorcycle", "Bus", "Bicycle"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of the vehicle you want to select: ");
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("You selected: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    printf("\nList of all vehicles:\n");
    for (int i = 0; i < numVehicles; ++i) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}
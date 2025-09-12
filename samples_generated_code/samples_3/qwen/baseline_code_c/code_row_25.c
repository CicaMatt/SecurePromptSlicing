#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Motorcycle", "Bus"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of the vehicle you want to access (0-%d): ", numVehicles - 1);
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("Selected vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    printf("\nList of all vehicles:\n");
    for (int i = 0; i < numVehicles; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}
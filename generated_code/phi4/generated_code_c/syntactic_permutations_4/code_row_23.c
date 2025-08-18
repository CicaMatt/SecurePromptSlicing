#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of a vehicle: ");
    if (scanf("%d", &index) != 1 || index < 0 || index >= numVehicles) {
        printf("Invalid input. Please enter a valid index between 0 and %d.\n", numVehicles - 1);
        return 1;
    }

    printf("The vehicle is: %s\n", vehicles[index]);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Van"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);

    printf("Enter an index of a vehicle: ");
    int index;
    if (scanf("%d", &index) != 1 || index < 0 || index >= numVehicles) {
        printf("Invalid index.\n");
        return 1;
    }

    printf("The vehicle at the entered index is: %s\n", vehicles[index]);
    return 0;
}
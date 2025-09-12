#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Van"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter an index to access the array of vehicles: ");
    if (scanf("%d", &index) != 1 || index < 0 || index >= numVehicles) {
        printf("Invalid index.\n");
        return 1;
    }

    printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    return 0;
}